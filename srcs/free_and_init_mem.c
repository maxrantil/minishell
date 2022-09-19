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
		env[i] = ft_strsep(&environ[i], "\n");			//use strsplit here to being able to manipulate the variables
		ft_printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
	env[i] = NULL;
		ft_printf("env[i]: %s\n", env[i]);
	return (env); 
	/* env = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
	i = 0;
	while (i < MSH_TOK_BUFSIZE) */
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
	ft_strdel(&msh->cli);
}