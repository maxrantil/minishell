/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:23:32 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 15:29:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*change_to_quote(char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		str++;
	return (str);
}

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

size_t	count_arguments(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (!ft_isspace(str))
		{
			while (!ft_isspace(str) && *str)
			{
				if (*str == '\'' || *str == '"')
					str = change_to_quote(str, *str);
				str++;
			}
			count++;
			if (*str == '\0')
				break ;
		}
		else
			str = skip_whitespaces(str);
		str++;
	}
	return (count);
}
