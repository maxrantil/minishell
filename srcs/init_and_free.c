/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*str_lvl;
	char	*ret;

	lvl = ft_atoi(ft_strchr(shlvl, '=') + 1);
	if (lvl <= 999)
		++lvl;
	else
		lvl = 1;
	str_lvl = ft_itoa(lvl);
	ret = ft_strnew(9);
	ft_strcpy(ret, "SHLVL=");
	ft_strcat(ret, str_lvl);
	ft_strdel(&str_lvl);
	return (ret);
}

size_t	env_arrlen(char **arr)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = -1;
	while (arr[++i])
	{
		if (!ft_strncmp(arr[i], "OLDPWD=", 7))
		 	continue ;
		len++;
	}
	return (len);
}

static char	**get_env(char **env)
{
	extern char	**environ;
	ssize_t		len;
	ssize_t		i;
	size_t		j;

	if (*environ)
	{
		len = env_arrlen(environ);
		// ft_printf("len %d\n", len);
		env = (char **)ft_memalloc(sizeof(char *) * (len + 1));// +1?
		j = 0;
		i = -1;
		while (environ[++i])
		{
			if (!ft_strncmp(environ[i], "SHLVL=", 6))
				env[j++] = change_shlvl(environ[i]);
			else if (!ft_strncmp(environ[i], "OLDPWD=", 7))
				continue ;
			else
				env[j++] = ft_strdup(environ[i]);
			// ft_printf("env = %s\n", env[j - 1]);
		}
			// ft_printf("0env = %s\n", env[j - 1]);
			// ft_printf("1env = %s\n", env[j]);
		env[j] = NULL;
		// ft_printf("env len : %d\n", ft_arrlen((void **)env));
		// for (int i=0;env[i];i++)
			// ft_printf("env[%d]%s\n", i, env[i]);
			// ft_printf("2env = %s\n", env[j]);
			// ft_printf("%s\n", environ[i]);
	}
	return (env);
}

void	init_msh(t_msh *msh)
{
	ft_printf("\n{blu}******************************************\n");
	ft_printf("\
	\t{yel}M{gre}I{red}N{blu}I{mag}S{blu}H{red}E{gre}L{yel}L{cya}\n");
	ft_printf("{blu}******************************************{nor}\n\n");
	msh->args = NULL;
	msh->paths = NULL;
	msh->cli = NULL;
	msh->env = NULL;
	msh->env = get_env(msh->env);
}

void	free_mem(t_msh *msh)
{
	if (msh->args)
	{
		ft_printf("HELLO\n");
		ft_printf("double out %p\n", msh->args);
		ft_printf("add of out %p\n", &msh->args);
		ft_arrfree((void *)msh->args, ft_arrlen((void **)msh->args));
		ft_memdel((void *)&msh->args);
	}
	if (msh->paths)
		ft_arrfree((void **)msh->paths, ft_arrlen((void **)msh->paths));
	ft_strdel(&msh->cli);
}
