/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 17:15:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	size_t	check;

	i = 1;
	check = 0;
	while (msh->args[i])
	{
		if (strchr(msh->args[i], '='))
		{
			loop_setenv(msh, msh->args[i]);
			check++;
		}
		i++;
	}
	return (check);
}
