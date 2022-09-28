/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 10:30:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (strchr(key_value, '='))
	{
		while (key_value[i] != '=')
			i++;
		ft_strncpy(key, key_value, i);
	}
	else
		ft_strcpy(key, key_value);
	ft_strcat(key, "=");
	return (key);
}

char	*ft_strtrim_quotes(char const *s)
{
	char		*st;
	size_t		sl;

	if (!s)
		return (NULL);
	while (*s == '\"')
		s++;
	sl = ft_strlen(s);
	if (*s)
		while (s[sl - 1] == '\"')
			sl--;
	st = ft_strsub(s, 0, sl);
	return (st);
}

int	get_tilde(t_msh *msh, char **tilde, size_t i)
{
	if (msh->args[i][1] == '-')
	{
		*tilde = get_env_value(msh->env, "OLDPWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else if (msh->args[i][1] == '+')
	{
		*tilde = get_env_value(msh->env, "PWD=");
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else
	{
		*tilde = get_env_value(msh->env, "HOME=");
		*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
	}
	return (1);
}
