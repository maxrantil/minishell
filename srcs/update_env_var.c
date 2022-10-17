/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/17 15:00:19 by mrantil          ###   ########.fr       */
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

static char	**change_pwd(char **env, char *cwd, char *key)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			ft_strdel(&env[i]);
			env[i] = ft_strjoin(key, cwd);
			return (env);
		}
		i++;
	}
	return (set_env_var(env, key, cwd));
}

char	**update_pwd(t_msh *msh, char *oldcwd)
{
	char	cwd[MAX_PATHLEN];

	msh->env = change_pwd(msh->env, oldcwd, "OLDPWD=");
	getcwd(cwd, sizeof(cwd));
	msh->env = change_pwd(msh->env, cwd, "PWD=");
	return (msh->env);
}
