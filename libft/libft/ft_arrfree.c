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

#include <stdio.h>
void	ft_arrfree(void **arr, size_t len)
{
	if (!arr || !len)
		return ;
	printf("1arrfree %p\n", arr[0]);
	printf("1add arrfree %p\n", &arr[0]);
	printf("2arrfree %p\n", *arr);
	printf("2add arrfree %p\n", &*arr);
	printf("3arrfree %p\n", arr);
	printf("3add arrfree %p\n", &arr);
	while (len--)
		ft_memdel(&arr[len]);
	ft_memdel(arr);
}
