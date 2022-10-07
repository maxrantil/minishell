/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 16:52:23 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	**switch_args(char **args, size_t len, size_t i)
{
	char	**new_args;
	size_t	j;

	new_args = \
	(char **)ft_memalloc(sizeof(char *) * (ft_arrlen((void **)&args[i]) + 1));
	if (!new_args)
		print_error(3);
	j = 0;
	while (args[i])
		new_args[j++] = ft_strdup(args[i++]);
	new_args[j] = NULL;
	ft_arrfree((void ***)&args, len);
	return (new_args);
}

static char	**set_tempenv(t_msh *msh, size_t i)
{
	char	**temp_env;
	size_t	len;
	size_t	x;

	len = 0;
	x = 1;
	while (msh->args[x] && ft_strchr(msh->args[x++], '='))
		len++;
	temp_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	if (!temp_env)
		print_error(3);
	x = 0;
	while (x < len)
		temp_env[x++] = ft_strdup(msh->args[i++]);
	temp_env[x] = NULL;
	return (temp_env);
}	

static int	env_heart(t_msh *msh, size_t arrlen)
{
	size_t	i;

	msh_setenv(msh);
	i = 1;
	msh->temp_env = set_tempenv(msh, i);
	while (msh->args[i] && ft_strchr(msh->args[i], '='))
		i++;
	if (i < arrlen)
	{
		msh->args = switch_args(msh->args, arrlen, i);
		msh_launch(msh);
		return (1);
	}
	return (0);
}

int	msh_env(t_msh *msh)
{
	size_t	i;
	size_t	arrlen;

	arrlen = ft_arrlen((void **)msh->args);
	if (arrlen > 1)
	{
		if (env_heart(msh, arrlen))
			return (1);
	}
	if (*msh->env)
	{
		i = 0;
		while (msh->env[i])
			ft_printf("%s\n", msh->env[i++]);
	}
	else
		ft_printf("minishell: env: environment is empty\n");
	return (1);
}

int	msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}
