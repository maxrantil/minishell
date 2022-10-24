/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/24 15:33:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	key = ft_strnew(ft_strlen(key_value));
	if (ft_strchr(key_value, '='))
	{
		while (key_value[i] != '=')
			i++;
		ft_strncpy(key, key_value, i);
	}
	else
		ft_strcpy(key, key_value);
	key = ft_strupdate(key, "=");
	return (key);
}

static void	free_table(t_builtin **ht)
{
	t_builtin	*tmp;
	int			i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (ht[i])
		{
			tmp = ht[i];
			while (tmp)
			{
				tmp = tmp->next;
				free(ht[i]);
				ht[i] = NULL;
				ht[i] = tmp;
			}
		}
		i++;
	}
}

void	free_mem(t_msh *msh, t_builtin **ht, ssize_t code)
{
	if (code == 1)
	{
		if (msh->temp_env)
		{
			msh_unsetenv(msh);
			ft_arrfree((void ***)&msh->temp_env, \
			ft_arrlen((void **)msh->temp_env));
		}
		if (msh->args)
			ft_arrfree((void ***)&msh->args, ft_arrlen((void **)msh->args));
		if (msh->paths)
			ft_arrfree((void ***)&msh->paths, ft_arrlen((void **)msh->paths));
		ft_strdel(&msh->cl);
	}
	if (code == 2)
	{
		if (msh->env)
			ft_arrfree((void ***)&msh->env, ft_arrlen((void **)msh->env));
		free_table(ht);
	}
}

int	find_matching_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
