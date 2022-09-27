/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:37:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/27 16:22:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*get_env_value(char **env, char *var)
{
	char	*ret;
	size_t	i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len))
		{
			ret = ft_strnew(ft_strlen(env[i]) - len); //+1 ?? if somehitng is missing in the value it needs +1
			ft_strcpy(ret, ft_strchr(env[i], '=') + 1);
			/* ft_strcat(ret, "\0"); */
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	**set_env_var(char **env, char *key, char *value, size_t i)
{
	char	**new_env;
	size_t	count;
	size_t	j;

	count = ft_arrlen(env);
	new_env = (char **)ft_memalloc(count + 1);
	j = 0;
	while (j < count)
	{
		new_env[j] = ft_strdup(env[j]);
		j++;
	}
	ft_arrfree(env, count);
	if (!value)
		new_env[j] = ft_strjoin(key, ft_strchr(new_env[i], '/'));
	else
		new_env[j] = ft_strjoin(key, value);
	new_env[++j] = NULL;
	return (new_env);
}

char	**unset_env_var(char **env, char *key)
{
	char	**new_env;
	size_t	count;
	size_t	i;
	size_t	j;

	count = ft_arrlen(env);
	new_env = (char **)ft_memalloc(count);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	ft_arrfree(env, count);
	return (new_env);
}
