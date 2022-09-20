/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:37:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/20 17:39:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>

char	*get_env_var(char **env, char *var)
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
			ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(env[i] - len));
			ft_strcpy(ret, ft_strchr(env[i], '/'));
			return (ret);
		}
		i++;
	}
	return (NULL);
}