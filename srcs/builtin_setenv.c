/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/30 09:43:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	loop_setenv(t_msh *msh)
{
	/* char	*key_value; */
	char	*key;
	size_t	i;

	i = 0;
	/* key_value = ft_strtrim_quotes(msh->args[1]); */
	key = extract_key(msh->args[1]);
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
	ft_strchr(msh->args[1], '=') + 1, 0);
	free(key);
	/* free(key_value); */
}

int	msh_setenv(t_msh *msh)
{
	if (ft_arrlen(msh->args) == 2)
	{
		if (strchr(msh->args[1], '='))
			loop_setenv(msh);
		else
		{
			ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
			return (2);
		}
	}
	else
	{
		ft_putstr_fd("error, you can only set one variable at a time.\n", \
		STDERR_FILENO);
		ft_putstr_fd("usage: 'setenv key=value'\n", STDERR_FILENO);
		return (2);
	}
	return (1);
}
