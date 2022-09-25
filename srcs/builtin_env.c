/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/20 17:22:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	while (key_value[i] != '=')
		i++;
	key = ft_strnew(ft_strlen(key_value));
	ft_strncpy(key, key_value, i);
	ft_strcat(key, "=");	//shall i do it without this? yeees..
	return (key);
}

//return 2 is error with continue
int	msh_setenv(t_msh *msh)
{
	char 	*key;
	char 	*key_value;
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
					//ft_putstr_fd("error: key is already set\n", STDERR_FILENO);
					ft_memset(msh->env[i], 0, ft_strlen(msh->env[i]));
					break ;
					/* Shall i just reset it if it exists? */
					//return (2);
				}
				i++;
			}
			free(key);
			key_value = ft_strdup(msh->args[1]); //will this be a leak?
			msh->env[i] = key_value;
			// msh->env[++i] = NULL;
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
		if (strchr(msh->args[1], '='))
			key = extract_key(msh->args[1]);
			// free(key);
			// char	*key_value = ft_strdup(msh->args[1]); //will this be a leak?
			// msh->env[i] = key_value;
			// msh->env[++i] = NULL;
		else
			key = msh->args[1];
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
			{
				/* Shall i just reset it if it exists? */
				ft_memset(msh->env[i], 0, ft_strlen(msh->env[i]));
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
