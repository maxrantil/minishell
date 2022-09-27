/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/27 10:41:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	**get_env()
{
	extern char	**environ;
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = (char **)ft_memalloc(sizeof(char *) * i);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "SHLVL=", 6))
			env[i] = change_shlvl(environ[i]);
		else
			env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (env); 
}

void	init_msh(t_msh *msh)
{
	ft_printf("\n{blu}******************"
        "************************\n");
	ft_printf("\
	\t{yel}M{gre}I{red}N{blu}I{mag}S{blu}H{red}E{gre}L{yel}L{cya}\n");
	ft_printf("{blu}*******************"
        "***********************{nor}\n\n");
	msh->args = NULL;
	msh->cli = NULL;
	msh->env = get_env();
}

void	free_mem(t_msh *msh)
{
	if (msh->args)
		ft_arrfree(msh->args, ft_arrlen(msh->args));
	ft_strdel(&msh->cli);
}