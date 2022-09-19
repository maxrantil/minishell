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
//- Run the following command "$> cd", then run "$> /bin/pwd". /bin/pwd must confirm that the current folder is the user's home folder.
//and more, look eval
int	msh_cd(t_msh *msh)
{
	if (!msh->args[1])
		ft_putstr_fd("./minishell: expected argument to \"cd\"\n", STDERR_FILENO);
	else
	{
		if (chdir(msh->args[1]) != 0) {
      	{
			ft_putstr_fd("error: could not change directory\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
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