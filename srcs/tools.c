/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 15:07:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_error(int i)
{
	if (i == 1)
		ft_putstr_fd("error, invalid argument\n", STDERR_FILENO);
	exit(1);
}

char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (strchr(key_value, '='))
	{
		while (key_value[i] != '=')
			i++;
		ft_strncpy(key, key_value, i);
	}
	else
		ft_strcpy(key, key_value);
	key = ft_strupdate(key, "=");
	return (key);
}

/* char	*ft_strtrim_quotes(char const *s)
{
	char		*st;
	size_t		sl;

	if (!s)
		return (NULL);
	while (*s == '\"')
		s++;
	sl = ft_strlen(s);
	if (*s)
		while (s[sl - 1] == '\"')
			sl--;
	st = ft_strsub(s, 0, sl);
	return (st);
} */
