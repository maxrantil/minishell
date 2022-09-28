/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:52:53 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 12:04:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	check_paths(t_msh *msh)
{
	char	*path;
	char	*dup_paths;
	size_t	i;
	size_t	j;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PATH=", 5))
		{
			msh->paths = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
			j = 0;
			dup_paths = ft_strdup(msh->env[i]);
			path = ft_strsep(&dup_paths, ":");
			while (path)
			{
				msh->paths[j++] = ft_strchr(path, '/');
				path = ft_strsep(&dup_paths, ":");
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*verify_arg(t_msh *msh)
{
	struct stat	statbuf;
	char		*verify;
	size_t		i;

	i = 0;
	while (msh->paths[i])
	{
		verify = (char *)ft_memalloc(sizeof(char) * MAX_PATHLEN);
		ft_strcpy(verify, msh->paths[i]);
		ft_strcat(verify, "/");
		ft_strcat(verify, msh->args[0]);
		if (!lstat(verify, &statbuf))
			return (verify);
		free(verify);
		i++;
	}
	return (NULL);
}

/* child process pid = 0 */
int	msh_launch(t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(msh->args[0], msh->args, msh->env) < 0)
		{
			check_paths(msh);
			execve(verify_arg(msh), msh->args, msh->env);
		}
		ft_printf("minishell: %s: ", msh->args[0]);
		ft_putstr_fd("command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("error: pid failed\n", STDERR_FILENO);
	else
		waitpid(pid, &status, WUNTRACED);
	return (1);
}
