/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/06 15:00:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t	count_quotes(char *p)
{
	int		found;
	int		quote;

	found = 1;
	while (*p)
	{
		if (*p == '\'' || *p == '"')
		{
			found = 0;
			quote = *p++;
			while (*p && *p != quote)
				p++;
			if (*p == quote)
				found = 1;
		}
		p++;
	}
	return (found);
}

static void	trim_cl(char **cl)
{
	char	*trimmed;

	trimmed = ft_strtrim(*cl);
	ft_strdel(cl);
	*cl = trimmed;
}

int	find_matching_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

static char	*find_matching_quote2(char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		str++;
	return (str);
}

int	find_argument_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_isspace(&str[i])))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += find_matching_quote(&str[i], str[i]);
		i++;
	}
	return (i);
}

//TEsst START HERE
char	**get_arguments(char *str, int argc)
{
	int		arg;
	char	**array;
	char	*begin;

	array = (char **)ft_memalloc(sizeof(char *) * (argc + 1));
	if (!array)
		print_error(3);
	arg = 0;
	while (*str)
	{
		if (!ft_isspace(str))
		{
			begin = str;
			while (*str && !ft_isspace((const char *)str))
				str++;
			array[arg++] = ft_strsub(begin, 0, str - begin);
		}
		if (*str)
			str++;
	}
	array[argc] = NULL;
	return (array);
}

int	skip_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isspace(&str[i]))
		{
			i++;
			while (ft_isspace(&str[i]) && str[i])
				i++;
			if (str[i])
				return (i - 1);
		}
	}
	return (0);
}

static char	*skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr) && *ptr)
		ptr++;
	return (ptr);
}

static size_t	count_arguments(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (!ft_isspace(str))
		{
			while (!ft_isspace(str) && *str)
			{
				if (*str == '\'' || *str == '"')
					str = find_matching_quote2(str, *str);
				str++;
			}
			count++;
			if (*str == '\0')
				break ;
		}
		else
			str = skip_whitespaces(str);
		str++;
	}
	return (count);
}

void	strip_quotes(char ***args, int argc)
{
	ssize_t	i;
	ssize_t	a;
	int		quote1;
	int		quote2;
	size_t	len;

	a = -1;
	while (++a < argc)
	{
		i = -1;
		len = ft_strlen((*args)[a]);
		while ((*args)[a][++i])
		{
			if ((*args)[a][i] == '\'' || (*args)[a][i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[a][i], (*args)[a][i]);
				quote2 += quote1;
				ft_memmove((void *)&(*args)[a][i], (void *)&(*args)[a][i + 1],len - quote1);
				ft_memmove((void *)&(*args)[a][quote2 - 1], (void *)&(*args)[a][quote2], len - quote2);
				i = quote2 - 2; // ?
			}
		}
	}
}

int	parser(t_msh *msh)
{
	int	argc;
	
	trim_cl(&msh->cl);
	if (*msh->cl)
	{
		if (!count_quotes(msh->cl))
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (-1);
		}
		argc = count_arguments(msh->cl);
		msh->args = get_arguments(msh->cl, argc);
		strip_quotes(&msh->args, argc);
		// split_args(msh, &msh->cl);
		change_variables(msh);
		return (1);
	}
	return (-1);
}
