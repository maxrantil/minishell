/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/11 11:41:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	print_echo(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		while (msh->args[i][j] != '\0')
			write(1, &msh->args[i][j++], 1);
		if (msh->args[i][0] != '\0')
			ft_putchar(' ');
		i++;
	}
}

int	msh_echo(t_msh *msh)
{
	print_echo(msh);
	ft_putchar('\n');
	return (1);
}
