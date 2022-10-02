/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 15:44:37 by mrantil          ###   ########.fr       */
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

static void	change_pwd(char **env, size_t i)
{
	char	cwd[MAX_PATHLEN];

	getcwd(cwd, sizeof(cwd));
	free(env[i]);
	env[i] = ft_strjoin("PWD=", cwd);
}

static char	**change_oldpwd(char **env, size_t i)
{
	size_t	j;

	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(env[j], "OLDPWD=", 7))
		{
			free(env[j]);
			env[j] = ft_strjoin("OLDPWD=", ft_strchr(env[i], '=') + 1);
			return (env);
		}
		j++;
	}
	return (set_env_var(env, "OLDPWD=", NULL, i));
}
char	**update_env_var(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "_=", 2))
		{
			free(msh->env[i]);
			msh->env[i] = change_underscore(msh);
		}
		i++;
	}
	return (msh->env);
}

char	**update_pwd(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PWD=", 4))
		{
			msh->env = change_oldpwd(msh->env, i);
			change_pwd(msh->env, i);
			return (msh->env);
		}
		i++;
	}
	return (msh->env);
}
