/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd_env_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/05 13:00:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

int	msh_env(t_msh *msh) // add so you can add temporary env variables
{
	/* struct stat	statbuf; */
	size_t	i;
	size_t	arrlen;
	int		status;

	i = 0;
	status = 0;
	arrlen = ft_arrlen((void **)msh->args);
	if (arrlen == 2)// && ft_strchr(msh->args[1], '=')) //this has the setenv error message
	{
		status = msh_setenv(msh);
		msh->temp_env = ft_strdup(msh->args[1]);
	}
	/* else if (arrlen <= 2 && !ft_strchr(msh->args[2], '=')) //this has the setenv error message
	{
		if (lstat(msh->args[2], &statbuf))
			execve(msh->args[2], msh->args, msh->env);
		ft_putstr_fd("minishell: ",STDERR_FILENO);
		ft_putstr_fd(msh->args[2], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	} */
	if (arrlen <= 2 && status != 2)
	{
		if (*msh->env)
		{
			while (msh->env[i])
				ft_printf("%s\n", msh->env[i++]);
		}
		else
			ft_printf("minishell: env: environment is empty\n");
	}
	/* else if (arrlen > 2) //errormessage is not correct, 
	{
		ft_putstr_fd("minishell: ",STDERR_FILENO);
		ft_putstr_fd(msh->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		print_error(2); //control so this message is right
	} */
	return (1);
}

int	msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}
