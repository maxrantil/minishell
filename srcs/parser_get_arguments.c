/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:30:36 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 18:50:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	find_argument_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_isspace(&str[i])))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_matching_quote(&str[i], str[i]);
		i++;
	}
	return (i);
}

char	**get_arguments(char *str, int argc)
{
	char	**array;
	ssize_t	i;
	size_t	j;
	size_t	arg;

	array = (char **)ft_memalloc(sizeof(char *) * (argc + 1));
	if (!array)
		print_error(NULL, 3);
	i = -1;
	arg = 0;
	while (str[++i])
	{
		if (!ft_isspace(&str[i]))
		{
			j = i;
			i = find_argument_len(&str[i]);
			array[arg++] = ft_strsub(str, (unsigned int)j, (size_t)i);
			i += j - 1;
		}
	}
	array[arg] = NULL;
	return (array);
}
