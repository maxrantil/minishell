/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 18:33:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	init_msh(t_msh *msh)
{
	ft_printf("\n******************"
        "************************");
	ft_printf("\n\t******MINISHELL******");
	ft_printf("\n\n\t-USE AT YOUR OWN RISK-");
	ft_printf("\n\n*******************"
        "***********************\n");
	msh->args = NULL;
	// msh->env = get_env();
}

static void	free_arr(char **arr, size_t len)
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
}

void	free_mem(char **args)
{
	if (args)
		free_arr(args, arr_len(args));
}