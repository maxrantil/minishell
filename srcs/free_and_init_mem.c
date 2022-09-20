/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_init_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/19 18:19:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*change_shlvl(char *shlvl)
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
	env = (char **)ft_memalloc(sizeof(char *) * i + 1);
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

/* static char	**get_env_from_env(char **environ)
{
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = (char **)ft_memalloc(sizeof(char *) * i + 1);
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
} */

void	init_msh(t_msh *msh)
{
	static int check;
	ft_printf("\n******************"
        "************************");
	ft_printf("\n\t******MINISHELL******");
	ft_printf("\n*******************"
        "***********************\n");
	msh->args = NULL;
	msh->cli = NULL;
	if (!check)
		msh->env = get_env();
	/* else
		msh->env = get_env_from_env(msh->env); */
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
	ft_strdel(&msh->cli);
}