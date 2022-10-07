/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 17:26:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*change_underscore(t_msh *msh)
{
	size_t	last_arg;

	last_arg = ft_arrlen((void **)msh->args) - 1;
	if (!ft_strncmp(msh->args[last_arg], "\0", 1) && last_arg > 0)
		--last_arg;
	return (ft_strjoin("_=", msh->args[last_arg]));
}

char	**update_env_var(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "_=", 2))
		{
			ft_strdel(&msh->env[i]);
			msh->env[i] = change_underscore(msh);
		}
		i++;
	}
	return (msh->env);
}

static char	**change_pwd(char **env, char *cwd)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			ft_strdel(&env[i]);
			env[i] = ft_strjoin("PWD=", cwd);
			return (env);
		}
		i++;
	}
	return (set_env_var(env, "PWD=", cwd));
}

static char	**change_oldpwd(char **env, char *oldcwd)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			ft_strdel(&env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldcwd);
			return (env);
		}
		i++;
	}
	return (set_env_var(env, "OLDPWD=", oldcwd));
}

char	**update_pwd(t_msh *msh, char *oldcwd)
{
	char	cwd[MAX_PATHLEN];

	msh->env = change_oldpwd(msh->env, oldcwd);
	getcwd(cwd, sizeof(cwd));
	msh->env = change_pwd(msh->env, cwd);
	return (msh->env);
}
