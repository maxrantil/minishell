/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:28:00 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/26 13:53:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*str_lvl;
	char	*ret;

	lvl = ft_atoi(ft_strchr(shlvl, '=') + 1);
	if (lvl <= 999)
		++lvl;
	else
		lvl = 1;
	str_lvl = ft_itoa(lvl);
	ret = ft_strnew(9);
	ft_strcpy(ret, "SHLVL=");
	ft_strcat(ret, str_lvl);
	ft_strdel(&str_lvl);
	return (ret);
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
			env[j] = ft_strjoin("OLDPWD=", ft_strchr(env[i], '/'));
			return (env);
		}
		j++;
	}
	return (set_env_var(env, "OLDPWD=", NULL, i));
}

char	**update_pwd(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			env = change_oldpwd(env, i);
			change_pwd(env, i);
		}
		i++;
	}
	return (env);
}
