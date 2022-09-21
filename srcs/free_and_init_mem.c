/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_init_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/20 15:14:06 by mrantil          ###   ########.fr       */
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
	env = (char **)ft_memalloc(sizeof(char *) * i + 100); //100 here is a hack for adding easily, +1 would be for null
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "SHLVL=", 6))
			env[i] = change_shlvl(environ[i]);				//this is malloced and needs to be free'ed
		else
			env[i] = ft_strsep(&environ[i], "\n");			//use strsplit here to being able to manipulate the variables
		ft_printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
	env[i] = NULL;
		ft_printf("env[i]: %s\n", env[i]);
	return (env); 
}

void	init_msh(t_msh *msh)
{
	ft_printf("\n******************"
        "************************");
	ft_printf("\n\t******MINISHELL******");
	ft_printf("\n*******************"
        "***********************\n");
	msh->args = NULL;
	msh->cli = NULL;
	msh->env = get_env();
}

/* static void	free_arr(char **arr, size_t len)
{
	if (!arr || !len)
		return ;
	while (len--)
	{
		if (arr[len] != NULL)
		{
			free(arr[len]);
			arr[len] = NULL;
		}
	}
	free(arr);
	arr = NULL;
}

static size_t	arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
} */

void	free_mem(t_msh *msh)
{
	free(msh->args);
	msh->args = NULL;
	/* if (msh->env)
		free_arr(msh->env, arr_len(msh->env)); */
	ft_strdel(&msh->cli);
}