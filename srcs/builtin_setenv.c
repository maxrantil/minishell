/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/24 09:08:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * It loops through the environment variables, and if it finds one that matches the key of the
 * argument, it unsets it, and then sets the new one
 * 
 * @param msh the main shell structure
 * @param arg the argument passed to setenv
 */
void	loop_setenv(t_msh *msh, char *arg)
{
	char	*key;
	size_t	i;

	i = 0;
	key = extract_key(arg);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
		{
			msh->env = unset_env_var(msh->env, key);
			break ;
		}
		i++;
	}
	msh->env = set_env_var(msh->env, key, \
	ft_strchr(arg, '=') + 1);
	ft_strdel(&key);
}

int	msh_setenv(t_msh *msh)
{
	size_t	i;

	i = 1;
	while (msh->args[i])
	{
		if (strchr(msh->args[i], '=') \
		&& (ft_isalpha(msh->args[i][0]) || msh->args[i][0] == '_'))
			loop_setenv(msh, msh->args[i]);
		else
			print_error(msh->args[i], 6);
		i++;
	}
	return (1);
}
