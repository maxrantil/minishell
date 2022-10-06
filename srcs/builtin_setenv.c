/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/05 11:39:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	loop_setenv(t_msh *msh, char *arg)
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
		if (strchr(msh->args[i], '='))
			loop_setenv(msh, msh->args[i]);
		else if (i < 2)
		{
			ft_putstr_fd("usage: 'setenv key=value'\n", STDERR_FILENO);
			return (2);
		}
		i++;

	}
	return (1);
}
