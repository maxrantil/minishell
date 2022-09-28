/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 16:34:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	**get_dollar(t_msh *msh, char *dollar, size_t j)
{
	char	*combo;
	size_t	i;

	i = 0;
	if (dollar)
	{
		combo = ft_strjoin(combo, dollar);
		combo = ft_strupdate(combo, "=");
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], combo, ft_strlen(combo)))
			{
				ft_memset(ft_strchr(msh->args[j], '$'), '\0', \
				ft_strlen(msh->args[j]) - ft_strlen(dollar) + 1);
				msh->args[j] = ft_strupdate(msh->args[j], \
				ft_strchr(msh->env[i], '=') + 1);
				break ;
			}
			i++;
		}
		free(combo);
		if (msh->env[i] == NULL)
			ft_memset((void *)msh->args[j], '\0', ft_strlen(msh->args[j]));
	}
	return (msh->args);
}

static void	check_tilde(t_msh *msh, size_t i)
{
	char	*tilde;

	if (get_tilde(msh, &tilde, i))
	{
		free(msh->args[i]);
		msh->args[i] = tilde;
	}
}

static char	**print_echo(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		j = 0;
		while (msh->args[i][j] != '\0')
		{
			if (msh->args[i][j] == '$')
				msh->args = get_dollar(msh, \
				ft_strchr(msh->args[i], '$') + 1, i);
			else if (msh->args[i][0] == '~')
				check_tilde(msh, i);
			if (msh->args[i][j] != '\"' && msh->args[i][j] != '\0')
				write(1, &msh->args[i][j], 1);
			j++;
		}
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
	return (msh->args);
}

static size_t	count_strings(char **args)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\"')
				++count;
			j++;
		}
		i++;
	}
	return (count);
}

int	msh_echo(t_msh *msh)
{
	size_t	count;

	count = count_strings(msh->args);
	if (count % 2 != 0)
	{
		ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
		return (2);
	}
	msh->args = print_echo(msh);
	ft_putchar('\n');
	return (1);
}
