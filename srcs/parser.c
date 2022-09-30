/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/29 17:53:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t	count_quotes(char *cli)	//check for single quotes needs to be implemented
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (cli[i])
	{
		if (cli[i] == '\"')
		{
			if (i == 0 || cli[i] != '\\')
				++count;
		}	
		i++;
	}
	return (count);
}

static int	check_quotes(char **cli)
{
	size_t	count;

	if (*cli)
	{
		count = count_quotes(*cli);
		if (count % 2 != 0)
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

static void	trim_cli(char **cli)
{
	char	*trimmed;

	trimmed = ft_strtrim(*cli);
	free(*cli);
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

static char	**split_tokens(char **cli, char *delimit)
{
	char	**tokens;
	char	*ptr;
	size_t	i;

	tokens = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
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
		if (*ptr == '"')
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
	tokens[i++] = NULL;
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

static char	**get_dollar(t_msh *msh, char *dollar, size_t j) //use ft_strsplit here to split the arguments of non aplpha to be able to combine dollars
{
	char	*combo;
	char	**dollars;
	size_t	i;
	size_t	b;

	dollars = ft_strsplit(dollar, '$');
	i = 0;
	while (dollars[i])
	{
		ft_printf("dollars %s\n", dollars[i]);
		i++;
	}
	ft_printf("dollars %s\n", dollars[i]);
	ft_printf("dollar %s\n", dollar);
	ft_printf("arg %s\n", msh->args[j]);
	i = 0;
	b = 0;
	char *new_arg;
	while (dollars[b])
	{
		combo = ft_strdup(dollars[b]);
		combo = ft_strupdate(combo, "=");
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], combo, ft_strlen(combo)))
			{
				// ft_memset(ft_strchr(msh->args[j], '$'), '\0', \
				ft_strlen(msh->args[j]) - ft_strlen(dollars[b]) + 1);
				// msh->args[j] = ft_strupdate(msh->args[j], \
				ft_strchr(msh->env[i], '=') + 1);
				new_arg = ft_strjoin(ft_strchr(msh->args[j], '$'), ft_strchr(msh->env[i], '=') + 1);
				// break ;
			}
			i++;
		}
		free(combo);
		/* if (msh->env[i] == NULL)
			ft_memset((void *)msh->args[j], '\0', ft_strlen(msh->args[j])); */
		b++;
	}
	return (msh->args);
}

static void	change_variables(t_msh *msh)
{
	char	*tilde;
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		j = 0;
		while (msh->args[i][j])
		{
			if (msh->args[i][0] == '~' && \
			(msh->args[i][1] == ' ' || msh->args[i][1] == '-' || \
			msh->args[i][0] == '+'))//try if echo ~max appends max or not in school if so add for + and - aswell
			{
				if (get_tilde(msh, &tilde, i)) 
				{
					free(msh->args[i]);
					msh->args[i] = tilde;
				}
			}
			if (msh->args[i][j] == '$')
				msh->args = get_dollar(msh, \
				ft_strchr(msh->args[i], '$'), i);
			j++;
		}
		i++;
	}
}

int	parser(t_msh *msh)
{
	if (!check_quotes(&msh->cli))
		return (0);
	trim_cli(&msh->cli);
	msh->args = split_tokens(&msh->cli, " \t"); 
	change_variables(msh);	///try in school what will show if you append letters to tilde variants
	return (1);
}
