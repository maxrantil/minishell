/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:37:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 13:53:27 by mrantil          ###   ########.fr       */
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
			ret = ft_strnew(ft_strlen(env[i]) - len);
			ft_strcpy(ret, ft_strchr(env[i], '=') + 1);
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
	ssize_t	j;

	count = ft_arrlen((void **)env);
	new_env = (char **)ft_memalloc(sizeof(char *) * (count + 1)); //+ 2? no dont think so
	j = -1;
	while (env[++j])
		new_env[j] = ft_strdup(env[j]);
	ft_arrfree((void **)env, count);
	ft_memdel((void *)&env);
	if (!value)
		new_env[j++] = ft_strjoin(key, ft_strchr(new_env[i], '=') + 1);
	else
		new_env[j++] = ft_strjoin(key, value);
	new_env[j] = NULL;
	return (new_env);
}

char	**unset_env_var(char **env, char *key)
{
	char	**new_env;
	size_t	count;
	size_t	i;
	size_t	j;

	count = ft_arrlen((void **)env);
	new_env = (char **)ft_memalloc(sizeof(char *) * (count - 1)); //check this -1
	i = 0;
	j = 0;
	while (i < count)//char it be =?
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_arrfree((void **)env, count);
	ft_memdel((void *)&env);
	return (new_env);
}
