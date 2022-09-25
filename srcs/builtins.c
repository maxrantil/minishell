/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/20 18:34:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_echo(t_msh *msh)		//do i need to take cli to get correct spaces? //double strings with quotes doesnt work now
{
	size_t	arrlen;
	size_t	i;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		if (i != arrlen && (ft_strchr(msh->args[i], '\"') || ft_strchr(msh->args[i], '\'')))
			ft_printf("%s", msh->args[i] + 1);
		else if (i == arrlen && (ft_strchr(msh->args[i], '\"') || ft_strchr(msh->args[i], '\'')))
			ft_printf("%.*s", ft_strlen(msh->args[i]) - 1, msh->args[i]);
		else
			ft_printf("%s", msh->args[i]);
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}

int	msh_pwd(t_msh *msh)
{
	char	cwd[MAX_PATHLEN];

	if (msh->args)
	{
		getcwd(cwd, sizeof(cwd));
		ft_printf("%s\n", cwd);
		return (1);	
	}
	return (0);
}

int	msh_env(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (msh->env[i][0])
			ft_printf("%s\n", msh->env[i]);
		i++;
	}
	return (1);
}



int msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}