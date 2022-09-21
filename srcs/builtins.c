/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:33:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/20 18:34:57 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_echo(t_msh *msh)		//do i need to take cli to get correct spaces? //double strings with quotes doesnt work now
{
	size_t	arrlen;
	size_t	i;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		if (i != arrlen && (ft_strchr(msh->args[i], '\"') || ft_strchr(msh->args[i], '\'')))
			ft_printf("%s", msh->args[i] + 1);
		else if (i == arrlen && (ft_strchr(msh->args[i], '\"') || ft_strchr(msh->args[i], '\'')))
			ft_printf("%.*s", ft_strlen(msh->args[i]) - 1, msh->args[i]);
		else
			ft_printf("%s", msh->args[i]);
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
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
char	*extract_key(char *key_value)
{
	char	*key;
	size_t	i;

	i = 0;
	while (key_value[i] != '=')
		i++;
	key = ft_strnew(ft_strlen(key_value));
	ft_strncpy(key, key_value, i);
	ft_strcat(key, "=");
	return (key);
}

int	msh_setenv(t_msh *msh)
{
	char 	*key;
	size_t	i;


	i = 0;
	if (ft_arrlen(msh->args) == 2)
	{
		if (strchr(msh->args[1], '='))
		{
			key = extract_key(msh->args[1]);
			while (msh->env[i])
			{
				if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
				{
					ft_putstr_fd("error: key is already set\n", STDERR_FILENO);
					/* Shall i just reset it if it exists? */
				}
				i++;
			}
			free(key);
			char	*key_value = ft_strdup(msh->args[1]); //will this be a leak?
			msh->env[i] = key_value;
			// msh->env[++i] = NULL;
		}
		else
		{
			ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("Error, you can only set one variable at a time\n", STDERR_FILENO);
		ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

//needs more testing for setenv and unsetenv!
int	msh_unsetenv(t_msh *msh)
{
	char 	*key;
	size_t	i;


	i = 0;
	if (ft_arrlen(msh->args) == 2)
	{
		if (strchr(msh->args[1], '='))
		{
			key = extract_key(msh->args[1]);
			while (msh->env[i])
			{
				if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
				{
					ft_memset(msh->env[i], 0, ft_strlen(msh->env[i]));
					/* Shall i just reset it if it exists? */
				}
				i++;
			}
			// free(key);
			// char	*key_value = ft_strdup(msh->args[1]); //will this be a leak?
			// msh->env[i] = key_value;
			// msh->env[++i] = NULL;
		}
		else
		{
			ft_putstr_fd("usage: unsetenv key=value\n", STDERR_FILENO);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("Error, you can only set one variable at a time\n", STDERR_FILENO);
		ft_putstr_fd("usage: setenv key=value\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int msh_exit(t_msh *msh)
{
	if (*msh->args)
		return (0);
	return (1);
}