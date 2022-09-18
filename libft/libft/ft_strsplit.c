/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:35:23 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:27:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countstrings(const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			x++;
		i++;
	}
	if (x == 0)
		x = 1;
	return (x);
}

static int	freearrays(char **arr, int x)
{
	while (x--)
	{
		if (arr[x])
		{
			free(arr[x]);
			arr[x] = NULL;
		}
	}
	free(arr);
	arr = NULL;
	return (0);
}

static int	count_letters(const char *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i + j + 1] != c && s[i + j + 1] != '\0')
		j++;
	return (j);
}

static int	cptoarray(char **arr, const char *s, char c)
{
	int	i;
	int	j;
	int	x;
	int	count;

	i = 0;
	j = 0;
	x = 0;
	while (s[i])
	{
		count = 0;
		if (s[i] != c)
		{
			j = i;
			count = count_letters(s, i, c);
			i += count;
			arr[x] = ft_strsub(s, j, count + 1);
			if (!arr[x])
				return (freearrays(arr, x));
			x++;
		}
		i++;
	}
	return (1);
}

char	**ft_strsplit(const char *s, char c)
{
	int		wrdlen;
	char	**arr;

	if (!s)
		return (NULL);
	wrdlen = countstrings(s, c);
	arr = (char **)ft_memalloc(sizeof(char *) * wrdlen + 1);
	if (arr && cptoarray(arr, s, c))
	{
		arr[wrdlen] = (char *)ft_memalloc(sizeof(char) + 1);
		if (!arr[wrdlen])
		{
			freearrays(arr, wrdlen);
			return (NULL);
		}
		arr[wrdlen] = NULL;
	}
	return (arr);
}
