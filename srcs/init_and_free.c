/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 10:51:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*str_lvl;
	char	*ret;

	lvl = ft_atoi(ft_strchr(shlvl, '=') + 1);
	if (lvl <= 999)
		++lvl;
	else
		lvl = 1;
	str_lvl = ft_itoa(lvl);
	ret = ft_strnew(9);
	ft_strcpy(ret, "SHLVL=");
	ft_strcat(ret, str_lvl);
	ft_strdel(&str_lvl);
	return (ret);
}

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
	ft_printf("\n{blu}******************************************\n");
	ft_printf("\
	\t{yel}M{gre}I{red}N{blu}I{mag}S{blu}H{red}E{gre}L{yel}L{cya}\n");
	ft_printf("{blu}******************************************{nor}\n\n");
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
