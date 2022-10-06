/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:52:53 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 17:31:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t	count_colon(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == ':')
			count++;
		str++;
	}
	return (count);
}

int	check_paths(t_msh *msh)
{
	char	*path;
	char	*dup_paths;
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PATH=", 5))
		{
			msh->paths = \
			(char **)ft_memalloc(sizeof(char *) * count_colon(msh->env[i]));
			dup_paths = ft_strdup(msh->env[i]);
			path = ft_strchr(dup_paths, '=') + 1;
			i = 0;
			while (path)
				msh->paths[i++] = ft_strdup(ft_strsep(&path, ":"));
			ft_strdel(&dup_paths);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*verify_arg(t_msh *msh)
{
	struct stat	statbuf;
	char		*verify;
	size_t		i;

	i = 0;
	while (msh->paths[i])
	{
		verify = ft_strjoin(msh->paths[i], "/");
		verify = ft_strupdate(verify, msh->args[0]);
		if (!lstat(verify, &statbuf))
		{
			ft_strdel(&msh->args[0]);
			msh->args[0] = ft_strdup(verify);
			ft_strdel(&verify);
			return (msh->args[0]);
		}
		ft_strdel(&verify);
		i++;
	}
	ft_strdel(&msh->args[0]);
	return (NULL);
}

int	msh_launch(t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(msh->args[0], msh->args, msh->env);
		msh->hold = ft_strdup(msh->args[0]);
		if (check_paths(msh))
			msh->args[0] = verify_arg(msh);
		execve(msh->args[0], msh->args, msh->env);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msh->hold, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("command not found\n", STDERR_FILENO);
		free_mem(msh, 1);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("error: pid failed\n", STDERR_FILENO);
	else
		waitpid(pid, &status, WUNTRACED);
	return (1);
}
