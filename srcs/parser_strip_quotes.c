/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_strip_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:18:22 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 15:32:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	strip_quotes(char **args)
{
	ssize_t	i;
	int		quote1;
	int		quote2;
	size_t	len;

	while (*args)
	{
		i = -1;
		len = ft_strlen(*args);
		while ((*args)[++i])
		{
			if ((*args)[i] == '\'' || (*args)[i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[i], (*args)[i]);
				quote2 += quote1;
				ft_memmove((void *)&(*args)[i], (void *)&(*args)[i + 1],  len - quote1);
				ft_memmove((void *)&(*args)[quote2 - 1], (void *)&(*args)[quote2], len - quote2);
				i = quote2 - 2;
			}
		}
		if (*args)
		args++;
	}
}
