/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:31:50 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/29 16:45:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = ft_strnew(len);
	if (!ss)
		return (NULL);
	while (len--)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}
