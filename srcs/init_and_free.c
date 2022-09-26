/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/26 15:37:47 by mrantil          ###   ########.fr       */
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
	env = (char **)ft_memalloc(sizeof(char *) * i); //100 here is a hack for adding easily, +1 would be for null
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "SHLVL=", 6))
			env[i] = change_shlvl(environ[i]);				//this is malloced and needs to be free'ed
		else
			env[i] = ft_strdup(environ[i]);			//use strsplit here to being able to manipulate the variables
		/* ft_printf("env[%d]: %s\n", i, env[i]); */
		i++;
	}
	/* env[i] = NULL;
		ft_printf("env[%d]: %s\n", i, env[i]); */
	return (env); 
}

void	init_msh(t_msh *msh)
{
	ft_printf("\n{blu}******************"
        "************************\n");
	ft_printf("\t{cya}****** \
	{yel}M{gre}I{red}N{blu}I{mag}S{blu}H{red}E{gre}L{yel}L{cya}******{nor}\n");
	ft_printf("{blu}*******************"
        "***********************{nor}\n\n");
	msh->args = NULL;
	msh->cli = NULL;
	msh->env = get_env();
}



void	free_mem(t_msh *msh)
{
	free(msh->args);
	msh->args = NULL;
	/* if (msh->env)
		free_arr(msh->env, arr_len(msh->env)); */
	ft_strdel(&msh->cli);
}