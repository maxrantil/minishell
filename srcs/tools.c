/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/05 11:41:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_error(int i)
{
	if (i == 1)
		ft_putstr_fd("error, invalid argument\n", STDERR_FILENO);
	else if (i == 2)
		ft_putstr_fd("usage: 'env key=value'\n", STDERR_FILENO);
	// exit(1);
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

void	free_mem(t_msh *msh)
{
	if (msh->temp_env)
	{
		/* printf("HELLO %s\n", msh->args[1]); */
		msh_unsetenv(msh);
		ft_strdel(&msh->temp_env);
		/* printf("HELLO\n"); */
	}
	if (msh->args)
	{
		ft_arrfree((void **)msh->args, ft_arrlen((void **)msh->args));
		ft_memdel((void *)&msh->args);
	}
	if (msh->paths)
	{
		ft_arrfree((void **)msh->paths, ft_arrlen((void **)msh->paths));
		// ft_memdel((void *)&msh->paths);
	}
	ft_strdel(&msh->cl);
	ft_strdel(&msh->hold);
}
