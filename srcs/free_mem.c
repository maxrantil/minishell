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

static void	free_array(void ***arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len)
	{
		if (*((*arr) + i))
		{
			free(*((*arr) + i));
			*((*arr) + i) = NULL;
		}
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static size_t	array_len(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	free_mem(char **args, char *cli)
{
	if (args)
		free_array((void ***)&args, array_len(args));
	if (cli)
		ft_strdel(&cli);
}