/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:29:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 14:39:34 by mrantil          ###   ########.fr       */
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
	// ft_printf("		---(%c)", quote);
	while (str[i] && str[i] != quote)
	{
		// ft_printf("(%s) ", &str[i]);
		i++;
	}
		// ft_printf("\n");
	return (i);
}

int	find_argument_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_isspace(&str[i])))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += find_matching_quote(&str[i], str[i]);
		i++;
	}
	return (i);
}

char	**get_arguments(char *str, int argc)
{
	int		i;
	int		j;
	int		arg;
	char	**array;

	array = (char **)ft_memalloc(sizeof(char *) * (argc + 1));
	if (!array)
		exit(3);
	i = -1;
	arg = 0;
	while (str[++i])
	{
		// ft_printf("(%d)->", i);
		if (!ft_isspace(&str[i]))
		{
			j = i;
			i = find_argument_len(&str[i]);
			array[arg++] = ft_strsub(str, (unsigned int)j, (size_t)i);
			i += j;
		}
		// ft_printf("(%d)\n", i);
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

int	ms_count_arguments(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		// ft_printf("s(%d)", i);
		if (!ft_isspace(&str[i]))
		{
			// ft_printf("	is(%d) ", i);
			while (!ft_isspace(&str[i]) && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i += find_matching_quote(&str[i], str[i]);
				i++;
			}
			ret++;
			// ft_printf("	ie(%d) ", i);
			if (str[i] == '\0')
				break ;
		}
		else
		{
			// ft_printf("	es(%d) ", i);
			i += skip_whitespace(&str[i]);
			// ft_printf("	ee(%d) ", i);
		}
		// ft_printf("e(%d)\n", i);
	}
	return (ret);
	// 	      7  10     17		  27='\0'
	// "hello "  "asddsa"  asd asd
}

void	strip_quotes(char ***args, int argc)
{
	int	i;
	int	a;
	int	quote1;
	int	quote2;
	int	len;

	a = -1;
	while (++a < argc)
	{
		i = -1;
		len = (int)ft_strlen((*args)[a]);
		// ft_printf("---(%s)len(%d)\n", (*args)[a], len);
		while ((*args)[a][++i])
		{
			if ((*args)[a][i] == '\'' || (*args)[a][i] == '"')
			{
				quote1 = i;
				quote2 = find_matching_quote(&(*args)[a][i], (*args)[a][i]);
				quote2 += quote1;

				// ft_printf("beg (%s)(%d - %d)\n", (*args)[a], quote1, quote2);
				ft_memmove((void *)&(*args)[a][i], (void *)&(*args)[a][i + 1],
					len - quote1);
				// ft_printf("mid (%s)(%d)(%d)\n", (*args)[a], quote1, quote2);

				// if ((*args)[a][quote2 - 1] == '\0')
				// {
				// 	*args[a][quote2 - 2] = '\0';
				// }
				// else
					ft_memmove((void *)&(*args)[a][quote2 - 1],
						(void *)&(*args)[a][quote2], len - quote2);
				// ft_printf("end (%s)(i=%d)\n", (*args)[a], i);

				i = quote2 - 2; // ?
			}
		}
	}
}

int	parser(t_msh *msh)
{
	int	argc;
	
	// argc = 0;
	trim_cl(&msh->cl);
	if (*msh->cl)
	{
		if (!count_quotes(msh->cl))
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (-1);
		}
		argc = ms_count_arguments(msh->cl);
		msh->args = get_arguments(msh->cl, argc);
		strip_quotes(&msh->args, argc);
		// split_args(msh, &msh->cl);
		change_variables(msh);
		return (1);
	}
	return (-1);
}
