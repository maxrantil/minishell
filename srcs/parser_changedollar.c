/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_changedollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 15:55:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*save_begin(t_msh *msh, size_t j)
{
	char	*begin_arg;
	size_t	len;

	len = ft_strclen(msh->args[j], '$');
	if (len)
	{
		begin_arg = ft_strsub(msh->args[j], 0, len);
		return (begin_arg);
	}
	return (NULL);
}

static void	change_new_arg(t_msh *msh, char **new_arg, size_t i)
{
	char	*temp;

	if (!*new_arg)
		*new_arg = ft_strnew(1);
	temp = ft_strdup(ft_strchr(msh->env[i], '=') + 1);
	*new_arg = ft_strupdate(*new_arg, temp);
	ft_strdel(&temp);
}

static char	*get_new_arg(t_msh *msh, char **dollars)
{
	char	*key;
	char	*new_arg;
	size_t	i;
	ssize_t	j;

	j = -1;
	new_arg = NULL;
	while (dollars[++j])
	{
		key = ft_strjoin(dollars[j], "=");
		i = 0;
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
			{
				change_new_arg(msh, &new_arg, i);
				break ;
			}
			i++;
		}
		ft_strdel(&key);
	}
	ft_arrfree((void **)dollars, ft_arrlen((void *)dollars));
	return (new_arg);
}

void	get_dollar(t_msh *msh, char *dollar, size_t i)
{
	char	**dollars;
	char	*new_arg;
	char	*begin_arg;

	begin_arg = save_begin(msh, i);
	dollars = ft_strsplit(dollar, '$');
	new_arg = get_new_arg(msh, dollars);
	if (begin_arg)
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_strupdate(begin_arg, new_arg);
	}
	else if (new_arg)
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_strdup(new_arg);
	}
	else
		ft_memset((void *)msh->args[i], '\0', ft_strlen(msh->args[i]));
	ft_strdel(&new_arg);
}
