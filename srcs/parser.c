/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/03 13:25:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t    count_quotes(char *str)
{
    int    i;
    int    found;
    int    quote;

    found = 1;
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            found = 0;
            quote = str[i++];
            while (str[i] != quote && str[i])
                i++;
            if (str[i] == quote)
                found = 1;
        }
    }
    return (found);
}

static void	trim_cl(char **cl)
{
	char	*trimmed;

	trimmed = ft_strtrim(*cl);
	ft_strdel(cl);
	*cl = trimmed;
}

static char *skip_whitespaces(char *cl)
{
	if (cl)
	{
		while (*cl && (*cl == ' ' || *cl == '\t'))
		{
			ft_printf("cl %s\n", cl);
			ft_printf("*cl %d\n", *cl);
			cl++;
		}
	}
	return (cl);
}

static int	count_arguments(char *str)
{
    int	args;
    int	i;
    int	quote;

    i = -1;
    args = 0;
    while (str[++i])
    {
        if (str[i] != '\t' && str[i] != ' ')
        {
            if (str[i] == '\'' || str[i] == '\"')
            {
                quote = str[i++];
                while (str[i] != quote)
                    i++;
            }
            else
            {
                while (str[i] != '\t' && str[i] != ' ' && str[i] && str[i] != '\'' && str[i] != '\"')
                	i++;
            }
            args++;
            if (!str[i])
                break;
        }
        else
        {
            while (str[i] == '\t' || str[i] == ' ')
                i++;
            i--;
        }
    }
    return (args);
}

static char	**split_args(t_msh *msh, char **cl, char *delimit)
{
	char	*ptr;
	size_t	i;
	size_t	count;

	count = count_arguments(*cl);
	msh->args = (char **)ft_memalloc(sizeof(char *) * count);
	if (!msh->args)
	{
		ft_putstr_fd("error: malloc args\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ptr = *cl;
	i = 0;
	// char *ptr_check;
	while (i < count)
	{
		// ptr_check = ptr;
		ptr = skip_whitespaces(ptr);
		// if (ptr_check == ptr)
			// ft_printf("SAME ADDRESS[%s]\n", ptr);
		if (*ptr == '"')
		{
			ptr++;
			msh->args[i++] = ft_strdup(strsep(&ptr, "\""));
		} 
		else if (*ptr == '\'')
		{
			ptr++;
			msh->args[i++] = ft_strdup(strsep(&ptr, "\'"));
		}
		else
			msh->args[i++] = ft_strdup(strsep(&ptr, delimit));
	}
	msh->args[i] = NULL;
	return (msh->args);
}

static int	get_tilde(t_msh *msh, char **tilde, size_t i)
{
	if (msh->args[i][1] == '-')
	{
		*tilde = get_env_value(msh->env, "OLDPWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else if (msh->args[i][1] == '+')
	{
		*tilde = get_env_value(msh->env, "PWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else
	{
		*tilde = get_env_value(msh->env, "HOME=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
	}
	return (1);
}

static char	*save_begin(t_msh *msh, size_t j)
{
	char	*begin_arg;
	size_t	len;

	len = ft_strclen(msh->args[j], '$');
	if (len)
	{
		begin_arg = ft_strsub(msh->args[j], 0, len);
		return (begin_arg);
	}
	return (NULL);
}

static char	*get_new_arg(t_msh *msh, char **dollars)
{
	char	*key;
	char	*new_arg;
	char	*temp;
	size_t	i;
	size_t	j;

	j = 0;
	new_arg = NULL;
	new_arg = ft_strnew(1); //thi is somehow a READ error later, i want to return it with NULL if it dosnt find and change.
	while (dollars[j])
	{
		key = ft_strdup(dollars[j]);
		key = ft_strupdate(key, "=");
		i = 0;
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
			{
				temp = ft_strdup(ft_strchr(msh->env[i], '=') + 1);
				new_arg = ft_strupdate(new_arg, temp);
				ft_strdel(&temp);
				break ;
			}
			i++;
		}
		ft_strdel(&key);
		j++;
	}
	ft_arrfree((void **)dollars, ft_arrlen((void *)dollars));
	ft_memdel((void *)&dollars);
	return (new_arg);
}

static void	get_dollar(t_msh *msh, char *dollar, size_t j)
{
	char	**dollars;
	char	*new_arg;
	char	*begin_arg;

	begin_arg = save_begin(msh, j);
	dollars = ft_strsplit(dollar, '$');
	new_arg = get_new_arg(msh, dollars);
	if (begin_arg)
	{
		ft_strdel(&msh->args[j]);
		msh->args[j] = ft_strupdate(begin_arg, new_arg);
	}
	else if (new_arg)
	{
		ft_strdel(&msh->args[j]);
		msh->args[j] = ft_strdup(new_arg);	
	}
	else
		ft_memset((void *)msh->args[j], '\0', ft_strlen(msh->args[j])); //here is a problem after it tries to read in loop in prwvious function.
		//ft_strdel(&msh->args[j]);
	ft_strdel(&new_arg);
}

static	size_t	check_tilde(char *str)
{
	size_t	i;

	i = 1;
	if (!str[i])
		return (1);
	if ((str[i] == '+' || str[i]== '-') && !str[i + 1])
		return (1);
	return (0);
}

static char	**change_variables(t_msh *msh)
{
	char	*tilde;
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		if (msh->args[i])
		{
			while (msh->args[i][j])
			{
				if (msh->args[i][0] == '~')
				{
					if (check_tilde(msh->args[i]))
					{
						if (get_tilde(msh, &tilde, i)) 
						{
							ft_strdel(&msh->args[i]);
							msh->args[i] = tilde;
						}
					}
				}
				else if (msh->args[i][j] == '$' && (msh->args[i][j + 1] == '_' || ft_isalpha(msh->args[i][j + 1]))) //ft_isascii as second parameter?
					get_dollar(msh, ft_strchr(msh->args[i], '$'), i);
				else if (msh->args[i][j] == '$' && msh->args[i][j + 1] == '$') //bonus fun, works alone but not if you append to end of another $variable
				{
					ft_strdel(&msh->args[i]);
					msh->args[i] = ft_itoa(getpid());
				}
				j++;
			}
		}
		i++;
	}
	return (msh->args);
}

int	parser(t_msh *msh)
{
	trim_cl(&msh->cl);
	if (*msh->cl)
	{
		if (!count_quotes(msh->cl))
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (0);
		}
		msh->args = split_args(msh, &msh->cl, " \t"); 
		msh->args = change_variables(msh);
		return (1);
	}
	return (-1);
}
