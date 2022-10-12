/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/12 16:48:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	loop_setenv(t_msh *msh, char *arg)
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
	if (!msh->env[i])
		return (0);
	return (1);
}

int	msh_setenv(t_msh *msh)
{
	size_t	i;

	i = 1;
	while (msh->args[i])
	{
		if (strchr(msh->args[i], '=') && (ft_isalpha(msh->args[i][0]) || msh->args[i][0] == '_'))
			loop_setenv(msh, msh->args[i]);
		else
			print_error(msh->args[i], 6);		
		i++;
	}
	return (1);
}
