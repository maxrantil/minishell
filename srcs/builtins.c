/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/19 16:34:02 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
//CD NEEDS MORE WORK! HIGH PRIORITY
//change from relative path s "$> cd relative/path/of/your/choice", then run the following command "$> /bin/pwd". /bin/pwd must confirm that the current folder was updated.
//and more, look eval

char	*get_env_var(char **env, char *var)
{
	char	*home;
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
		{
			home = (char *)ft_memalloc(sizeof(char) * ft_strlen(env[i] - 5));
			ft_strcpy(home, ft_strchr(env[i], '/'));
			return (home);
		}
		i++;
	}
	return (NULL);
}

int	msh_cd(t_msh *msh)
{
	if (!msh->args[1])
		chdir(get_env_var(msh->env, "HOME="));
	else if (!ft_strcmp(msh->args[1], "-"))
	{
		chdir(get_env_var(msh->env, "OLDPWD="));
	}
	else
	{
		if (chdir(msh->args[1]) != 0)
		{
			ft_printf("minishell: cd: %s", msh->args[1]);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);			///control for iMac
		}
	}
	return 1;
}

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

int	msh_env(t_msh *msh)
{
	size_t	i;

	i = 0;
	while (msh->env[i])
		ft_printf("%s\n", msh->env[i++]);
	return (1);
}

//after CD next priotity is setenv and unsetenv
/* int	msh_setenv(t_msh *msh)
{
	size_t	i;

	i = 0;
	
	return (1);
} */

/* int	msh_unsetenv(t_msh *msh)
{
	size_t	i;

	i = 0;
	
	return (1);
} */

int msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}