/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/12 20:36:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	**switch_args(char **args, size_t arglen, size_t i)
{
	char	**new_args;
	size_t	j;

	new_args = \
	(char **)ft_memalloc(sizeof(char *) * (arglen - i + 1));
	j = 0;
	while (args[i])
		new_args[j++] = ft_strdup(args[i++]);
	new_args[j] = NULL;
	ft_arrfree((void ***)&args, arglen);
	return (new_args);
}

static char	**set_tempenv(t_msh *msh)
{
	char	**temp_env;
	size_t	i;
	size_t	len;

	temp_env = NULL;
	len = 0;
	i = 1;
	while (msh->args[i] && ft_strchr(msh->args[i++], '='))
		len++;
	if (len)
	{
		temp_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
		i = 0;
		while (i++ < len)
			temp_env[i - 1] = ft_strdup(msh->args[i]);
		temp_env[i - 1] = NULL;
	}
	return (temp_env);
}	

static int	env_heart(t_msh *msh, size_t arglen)
{
	size_t	i;

	i = 0;
	while (msh->args[++i] && ft_strchr(msh->args[i], '='))
		loop_setenv(msh, msh->args[i]);
	msh->temp_env = set_tempenv(msh);
	if (i < arglen)
	{
		msh->args = switch_args(msh->args, arglen, i);
		msh_launch(msh);
		return (1);
	}
	return (0);
}

int	msh_env(t_msh *msh)
{
	size_t	i;
	size_t	arglen;

	arglen = ft_arrlen((void **)msh->args);
	if (arglen > 1)
	{
		if (env_heart(msh, arglen))
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
