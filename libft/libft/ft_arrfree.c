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

void	ft_arrfree(char **arr, size_t len)
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
