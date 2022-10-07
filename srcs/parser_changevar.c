/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_changevar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 15:15:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	find_variables(t_msh *msh, size_t i, size_t j)
{
	if (msh->args[i][0] == '~')
		tilde(msh, i);
	else if (msh->args[i][j] == '$' && (msh->args[i][j + 1] == '_' \
	|| ft_isalpha(msh->args[i][j + 1])))
		get_dollar(msh, ft_strchr(msh->args[i], '$'), i);
	else if (msh->args[i][j] == '$' && msh->args[i][j + 1] == '$')
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_itoa(getpid());
	}
}

void	change_variables(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		if (msh->args[i])
		{
			while (msh->args[i][j] != '\0')
			{
				find_variables(msh, i, j);
				j++;
			}
		}
		i++;
	}
}
