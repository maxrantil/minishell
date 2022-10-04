/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_splitargs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:17 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 15:24:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr))
		ptr++;
	return (ptr);
}

static int	count_arguments(char *p)
{
	int		quote;
	size_t	args;

	args = 0;
	while (*p)
	{
		p = skip_whitespaces(p);
		if (*p == '"' || *p == '\'')
		{
			quote = *p++;
			while (*p && *p != quote)
				p++;
			args++;
			p++;
		}
		else if (*p)
		{
			while (*p && !ft_isspace((const char *)p) \
			&& *p != '"' && *p != '\'')
				p++;
			args++;
		}
	}
	return (args);
}

static char	*loop_args(t_msh *msh, char *p, size_t i)
{
	char	*begin;
	int		quote;

	if (*p == '"' || *p == '\'')
	{
		quote = *p++;
		begin = p;
		while (*p && *p != quote)
			p++;
		msh->args[i] = ft_strsub(begin, 0, p - begin);
		p++;
	}
	else if (*p)
	{
		begin = p;
		while (*p && !ft_isspace((const char *)p) && *p != '"' && *p != '\'')
			p++;
		msh->args[i] = ft_strsub(begin, 0, p - begin);
	}
	else
		print_error(1);
	return (p);
}

void	split_args(t_msh *msh, char **cl)
{
	char	*p;
	char	*p_check;
	int		count;
	int		i;

	count = count_arguments(*cl);
	msh->args = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	if (!msh->args)
	{
		ft_putstr_fd("error: malloc args\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	p = *cl;
	i = -1;
	while (++i < count)
	{
		p_check = p;
		p = skip_whitespaces(p);
		if (p_check != p && i > 1)
		msh->args[i - 1] = ft_strupdate(msh->args[i - 1], " ");
		p = loop_args(msh, p, i);
	}
	msh->args[i] = NULL;
}
