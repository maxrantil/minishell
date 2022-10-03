/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:22:46 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/03 09:53:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	loop_for_unsetenv(t_msh *msh)
{
	char	*key;
	size_t	i;
	size_t	len;

	i = 0;
	key = extract_key(msh->args[1]);
	len = ft_strlen(key);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], key, len))
		{
			/* if (!ft_strncmp(key, "PWD=", 4)) // delete this
			{
				ft_putstr_fd("error, you are not allowed to unset PWD.\n", \
				STDERR_FILENO);
				free(key);
				return (2);
			} */
			msh->env = unset_env_var(msh->env, key);
			break ;
			// ft_strdel(&key);
			// return (1);
		}
		i++;
	}
	ft_strdel(&key);
	return (1);
}

int	msh_unsetenv(t_msh *msh)
{
	int	ret;

	ret = 1;
	if (ft_arrlen((void **)msh->args) == 2)
		ret = loop_for_unsetenv(msh);
	else
	{
		ft_putstr_fd("error, you can only unset one variable at a time.\n", \
		STDERR_FILENO);
		ft_putstr_fd("usage: 'unsetenv key=value', or 'unsetenv key'\n", \
		STDERR_FILENO);
		return (2);
	}
	return (ret);
}
