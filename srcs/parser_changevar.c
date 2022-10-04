/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_changevar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:11 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 15:56:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	get_tilde(t_msh *msh, char **tilde, size_t i)
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
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else
	{
		*tilde = get_env_value(msh->env, "HOME=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
	}
	return (1);
}

static size_t	check_tilde(char *str)
{
	size_t	i;

	i = 1;
	if (!str[i])
		return (1);
	if ((str[i] == '+' || str[i] == '-') && !str[i + 1])
		return (1);
	return (0);
}

static void	find_variables(t_msh *msh, size_t i, size_t j)
{
	char	*tilde;

	if (msh->args[i][0] == '~')
	{
		if (check_tilde(msh->args[i]))
		{
			if (get_tilde(msh, &tilde, i))
			{
				ft_strdel(&msh->args[i]);
				msh->args[i] = tilde;
			}
		}
	}
	else if (msh->args[i][j] == '$' && (msh->args[i][j + 1] == '_' \
	|| ft_isalpha(msh->args[i][j + 1])))
		get_dollar(msh, ft_strchr(msh->args[i], '$'), i);
	else if (msh->args[i][j] == '$' && msh->args[i][j + 1] == '$')
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_itoa(getpid());
	}
}

void	change_variables(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		if (msh->args[i])
		{
			while (msh->args[i][j] != '\0')
			{
				find_variables(msh, i, j);
				j++;
			}
		}
		i++;
	}
}
