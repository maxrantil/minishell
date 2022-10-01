/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/30 17:58:16 by mrantil          ###   ########.fr       */
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

static void	trim_cli(char **cli)
{
	char	*trimmed;

	trimmed = ft_strtrim(*cli);
	ft_strdel(cli);
	*cli = trimmed;
}

static char *skip_whitespaces(char *cli)
{
	if (cli)
	{
		while (*cli && ft_isspace(cli))
			cli++;
	}
	return (cli);
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

static char	**split_tokens(char **cli, char *delimit)
{
	char	**tokens;
	char	*ptr;
	size_t	i;

	tokens = (char **)ft_memalloc(sizeof(char *) * count_arguments(*cli));
	if (!tokens)
	{
		ft_putstr_fd("error: malloc tokens\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ptr = *cli;
	i = 0;
	while (ptr)
	{
		ptr = skip_whitespaces(ptr);
		if (*ptr == '"' || *ptr == '\'')
		{
			ptr++;
			tokens[i++] = ft_strdup(strsep(&ptr, "\""));
		}
		else if (*ptr == '\'')
		{
			ptr++;
			tokens[i++] = ft_strdup(strsep(&ptr, "\'"));
		}
		else
			tokens[i++] = ft_strdup(strsep(&ptr, delimit));
	}
	tokens[i] = NULL;
	return (tokens);
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
	new_arg = ft_strnew(1);
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
		free(dollars[j]);
		j++;
	}
	free(dollars);
	// ft_arrfree(dollars, ft_arrlen(dollars));
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
		ft_memset((void *)msh->args[j], '\0', ft_strlen(msh->args[j])); //will this be able to get freed?
	ft_strdel(&new_arg);
	/* return (msh->args[j]); */
}

static char	**change_variables(t_msh *msh)
{
	char	*tilde;
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen) //take away =?
	{
		j = 0;
		while (msh->args[i][j])
		{
			if (msh->args[i][0] == '~' && \
			(msh->args[i][1] == ' ' || msh->args[i][1] == '-' || \
			msh->args[i][1] == '+' || msh->args[i][1] == '\0'))//try if echo ~max appends max or not in school if so add for + and - aswell YES IT DOES
			{
				if (get_tilde(msh, &tilde, i)) 
				{
					ft_strdel(&msh->args[i]);
					msh->args[i] = tilde;
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
		i++;
	}
	return (msh->args);
}

int	parser(t_msh *msh)
{
	if (*msh->cli)
	{
		if (!count_quotes(msh->cli))
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (0);
		}
		trim_cli(&msh->cli);
		msh->args = split_tokens(&msh->cli, " \t"); 
		msh->args = change_variables(msh);	///try in school what will show if you append letters to tilde variants
		return (1);
	}
	return (0);
}
