/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 17:16:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"



/* static void	check_tilde(t_msh *msh, size_t i)
{
	char	*tilde;

	if (get_tilde(msh, &tilde, i))
	{
		free(msh->args[i]);
		msh->args[i] = tilde;
	}
} */

static char	**print_echo(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		j = 0;
		while (msh->args[i][j] != '\0')
			write(1, &msh->args[i][j++], 1);
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
	return (msh->args);
}



int	msh_echo(t_msh *msh)
{
	msh->args = print_echo(msh);
	ft_putchar('\n');
	return (1);
}
