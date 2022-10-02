/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:52:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/26 10:53:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree(void **arr, size_t len)
{
	// size_t	i;

	if (!arr || !len)
		return ;
	// i = 0;
	while (len--)
	{
		// if (arr[len] != NULL)
		// {
			ft_memdel(arr[len]);
			// free(arr[len]);
			// arr[len] = NULL;
			// ft_strdel(&arr[len]);
		// }
		// i++;
	}
	// ft_strdel(arr);
	ft_memdel(*arr);
	// free(arr);
	// arr = NULL;
}
