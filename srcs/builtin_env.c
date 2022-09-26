/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/26 16:26:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (strchr(key_value, '='))
	{
		while (key_value[i] != '=')
			i++;
		ft_strncpy(key, key_value, i);
	}
	else
		ft_strcpy(key, key_value);
	ft_strcat(key, "=");
	return (key);
}

//return 2 is error with continue
int	msh_setenv(t_msh *msh)
{
	char 	*key;
	size_t	i;


	i = 0;
	if (ft_arrlen(msh->args) == 2)
	{
		if (strchr(msh->args[1], '='))
		{
			key = extract_key(msh->args[1]);
			while (msh->env[i])
			{
				if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
				{
					ft_memset(msh->env[i], 0, ft_strlen(msh->env[i])); //dup the old into a new without the one
					break ;
				}
				i++;
			}
			msh->env = set_env_var(msh->env, key, ft_strchr(msh->args[1], '=') + 1, 0);
			free(key);
		}
		else
		{
			ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
			return (2);
		}
	}
	else
	{
		ft_putstr_fd("Error, you can only set one variable at a time\n", STDERR_FILENO);
		ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
		return (2);
	}
	return (1);
}

//needs more testing for setenv and unsetenv!
int	msh_unsetenv(t_msh *msh)
{
	char 	*key;
	size_t	i;


	i = 0;
	if (ft_arrlen(msh->args) == 2)
	{
		key = extract_key(msh->args[1]);
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
			{
				if (!ft_strncmp(key, "PWD=", 4) || !ft_strncmp(key, "OLDPWD=", 7))
					return (2);
				msh->env = unset_env_var(msh->env, key); //doesnt continue, check it!
				free(key);
				return (1);
			}
			i++;
		}
	}
	else
	{
		ft_putstr_fd("Error, you can only unset one variable at a time\n", STDERR_FILENO);
		ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
		return (2);
	}
	return (1);
}
