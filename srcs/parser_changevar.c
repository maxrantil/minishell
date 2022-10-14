/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_changevar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 19:16:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t	find_variables(t_msh *msh, size_t i, size_t j)
{
	if (msh->args[i][j] == '~' && j == 0)
	{
		tilde(msh, i);
	}
	if (msh->args[i][j] == '$' \
	&& (msh->args[i][j + 1] == '_' \
	|| ft_isalnum(msh->args[i][j + 1])))
	{
		get_dollar(msh, ft_strchr(msh->args[i], '$'), i);
		return (1);
	}
	else if (msh->args[i][j] == '$' \
	&& msh->args[i][j + 1] == '$')
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_itoa(getpid());
	}
	return (0);
}

void	change_variables(t_msh *msh)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (msh->args[i])
	{
		j = 0;
		while (msh->args[i][j])
		{
			if (find_variables(msh, i, j))
				break ;
			j++;
		}
		i++;
	}
}
