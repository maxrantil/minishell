/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:16:41 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 17:17:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	exec_tilde(char *arg)
{
	if (chdir(arg) != 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
}

static void	exec_dash(char **env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD=");
	if (chdir(oldpwd) != 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	ft_strdel(&oldpwd);
}

static void	exec_home(char **env)
{
	char	*home;

	home = get_env_value(env, "HOME=");
	if (chdir(home) != 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	ft_strdel(&home);
}

int	msh_cd(t_msh *msh)
{
	char	cwd[MAX_PATHLEN];

	getcwd(cwd, sizeof(cwd));
	if (ft_arrlen((void **)msh->args) <= 2)
	{
		if (!msh->args[1])
			exec_home(msh->env);
		else if (!ft_strcmp(msh->args[1], "-"))
			exec_dash(msh->env);
		else if (!ft_strcmp(msh->args[1], "~"))
			exec_tilde(msh->args[1]);
		else
		{
			if (chdir(msh->args[1]) != 0)
			{
				ft_printf("minishell: cd: %s", msh->args[1]);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			}
		}
		msh->env = update_pwd(msh, cwd);
	}
	else
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	return (1);
}
