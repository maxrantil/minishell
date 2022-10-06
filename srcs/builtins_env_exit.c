/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd_env_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/05 13:00:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	**switch_args(char **args, size_t len, size_t i)
{
	char	**new_args;
	size_t	j;

	new_args = (char **)ft_memalloc(sizeof(char *) * len);
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
	while (ft_strchr(msh->args[x++], '='))
		len++;
	temp_env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	if (!temp_env)
		print_error(3);
	x = 0;
	while (x <= len)
		temp_env[x++] = ft_strdup(msh->args[i++]);
	temp_env[x] = NULL;
	return (temp_env);
}	


int	msh_env(t_msh *msh)
{
	size_t	i;
	size_t	arrlen;
	int		status;

	status = 0;
	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	if (arrlen == 2 && ft_strchr(msh->args[i], '=')) //this has the setenv error message
	{
		status = msh_setenv(msh);
		msh->temp_env = set_tempenv(msh, i);
	}
	if (arrlen <= 2 && status == 0)
	{
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
	else if (!ft_strchr(msh->args[1], '=') && arrlen > 1)
		msh->args = switch_args(msh->args, arrlen, 1);
	else if (arrlen > 2)
	{
		status = msh_setenv(msh);
		i = 0;
		msh->temp_env = set_tempenv(msh, i);
		msh->args = switch_args(msh->args, arrlen - 1, 2);
	}
	msh_launch(msh);
	return (1);
}

int	msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}
