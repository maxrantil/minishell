/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 19:30:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int    check_address(char *addr)
{
    if (access(addr, F_OK) != 0)
        return (-1); // Doesn't Exist
    if (access(addr, X_OK) != 0)
        return (-2); // No access
    return (0); // Ready to feed addr to either execve or cd
}

static void	print_usage(char *arg)
{
	if (ft_strequ(arg, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", \
		STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	}
}

void	print_error(char *arg, int i)
{
	if (i == 1)
		ft_putstr_fd("error, invalid argument\n", STDERR_FILENO);
	else if (i == 2)
		ft_putstr_fd("usage: 'env key=value'\n", STDERR_FILENO);
	else if (i == 3)
	{
		ft_putstr_fd("error, malloc error\n", STDERR_FILENO);
		exit(1);
	}
	else if (i == 4)
		print_usage(arg);
}

char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (ft_strchr(key_value, '='))
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

void	free_mem(t_msh *msh, ssize_t code)
{
	if (code == 1)
	{
		if (msh->temp_env)
		{
			msh_unsetenv(msh);
			ft_arrfree(\
			(void ***)&msh->temp_env, ft_arrlen((void **)msh->temp_env));
		}
		if (msh->args)
			ft_arrfree((void ***)&msh->args, ft_arrlen((void **)msh->args));
		if (msh->paths)
			ft_arrfree((void ***)&msh->paths, ft_arrlen((void **)msh->paths));
		ft_strdel(&msh->cl);
	}
	if (code == 2 && msh->env)
		ft_arrfree((void ***)&msh->env, ft_arrlen((void **)msh->env));
}

int	find_matching_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
