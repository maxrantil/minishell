/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd_env_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 17:18:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_pwd(t_msh *msh)
{
	char	cwd[MAX_PATHLEN];

	if (msh->args)
	{
		getcwd(cwd, sizeof(cwd));
		ft_printf("%s\n", cwd);
		return (1);
	}
	return (0);
}

int	msh_env(t_msh *msh) // add so you can add temporary env variables
{
	size_t	i;
	size_t	arrlen;

	i = 0;
	arrlen = ft_arrlen((void **)msh->args);
	if (arrlen == 2) //this has the setenv error message
	{
		msh->temp_env_flag = 1;
		msh_setenv(msh);
		msh->temp_env = ft_strdup(msh->args[1]);
	}
	if (arrlen <= 2)
	{
		if (*msh->env)
		{
			while (msh->env[i])
				ft_printf("%s\n", msh->env[i++]);
		}
		else
			ft_printf("minishell: env: environment is empty\n");
	}
	else if (arrlen > 2) 
		print_error(2); //control so this message is right
	return (1);
}

int	msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}
