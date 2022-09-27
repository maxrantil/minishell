/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/27 16:02:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_pwd(t_msh *msh)
{
	char	cwd[MAX_PATHLEN];

	if (msh->args)
	{
		getcwd(cwd, sizeof(cwd));
		ft_printf("%s\n", cwd);
		return (1);	
	}
	return (0);
}

int	msh_env(t_msh *msh)
{
	size_t	i;

	i = 0;
	if (ft_arrlen(msh->args) == 1)
	{
		while (msh->env[i])
			ft_printf("%s\n", msh->env[i++]);
	}
	return (1);
}

int msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}
