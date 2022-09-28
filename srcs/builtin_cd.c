/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:16:41 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 15:49:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	exec_tilde(t_msh *msh)
{
	char	*tilde;

	get_tilde(msh, &tilde, 1); //change so it will work even if unset HOME is done
	if (chdir(tilde) != 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	free(tilde);
}

static void	exec_dash(char **env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD=");
	if (chdir(oldpwd) != 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	free(oldpwd);
}

static void	exec_home(char **env)
{
	char	*home;

	home = get_env_value(env, "HOME=");
	if (chdir(home) != 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	free(home);
}

int	msh_cd(t_msh *msh)
{
	if (!msh->args[1])
		exec_home(msh->env);
	else if (!ft_strcmp(msh->args[1], "-"))
		exec_dash(msh->env);
	else if (msh->args[1][0] == '~')
		exec_tilde(msh);
	else
	{
		if (chdir(msh->args[1]) != 0)
		{
			ft_printf("minishell: cd: %s", msh->args[1]);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
	}
	msh->env = update_pwd(msh);
	return (1);
}
