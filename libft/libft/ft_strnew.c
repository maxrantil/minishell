/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:52:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 20:02:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(size + 1);
	if (!str)
	{
		ft_putstr_fd("error, malloc error\n", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(str, size + 1);
	return (str);
}
