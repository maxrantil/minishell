/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/27 16:35:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*get_tilde(t_msh *msh, char *arg, size_t i)
{
	char	*tilde;

	if (arg[1] == '-')
	{
		tilde = get_env_value(msh->env, "OLDPWD=");
		if (!tilde)
			return (NULL);
	}
	else
		tilde = get_env_value(msh->env, "HOME=");
	// free(arg);
	ft_strjoin(tilde, msh->args[i] + ft_strlen(arg));// this is maybe error but i need to combine if echo ~/foo for example
	return (tilde);
}

static char	**get_dollar(t_msh *msh, char *dollar, size_t j)
{
	char	*combo;
	size_t	i;

	i = 0;
	if (dollar)
	{
		combo = ft_strnew(MAX_PATHLEN);
		ft_strcpy(combo, dollar);
		ft_strcat(combo, "=");
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], combo, ft_strlen(combo)))
			{
				free(msh->args[j]);
				msh->args[j] = ft_strdup(ft_strchr(msh->env[i], '=') + 1); //use ft_strupdate?
			}
			i++;
		}
		free(combo);
	}
	return (msh->args);
}

static char **print_echo(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		j = 0;
		while (msh->args[i][j] != '\0')
		{
			if (msh->args[i][0] == '$')
				msh->args = get_dollar(msh, ft_strchr(msh->args[i], '$') + 1, i);
			else if (msh->args[i][0] == '~')
				msh->args[i] = get_tilde(msh, msh->args[i], i);
			if (msh->args[i][j] != '\"' || msh->args[i][j] != '\0')
				write(1, &msh->args[i][j], 1);
			j++;
		}
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
	return (msh->args);
}

static size_t	count_strings(char **args)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\"')
				++count;
			j++;
		}
		i++;
	}
	return (count);
}

int	msh_echo(t_msh *msh)
{
	size_t	count;

	count = count_strings(msh->args);
	if (count % 2 != 0)
	{
		ft_putstr_fd("error, double quotes don't match\n", STDERR_FILENO);
		return (2);
	}
	msh->args = print_echo(msh);
	ft_putchar('\n');
	return (1);
}
