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
		/* if (!ft_strncmp(arr[i], "OLDPWD=", 7))
			continue ; */
		len++;
	}
	return (len);
}

static char	**get_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;

	env = NULL;
	if (*environ)
	{
		env = (char **)ft_memalloc(sizeof(char *) * env_arrlen(environ));
		i = -1;
		while (environ[++i])
		{
			if (!ft_strncmp(environ[i], "SHLVL=", 6))
				env[i] = change_shlvl(environ[i]);
			/* else if (!ft_strncmp(environ[i], "OLDPWD=", 7))	//will this give me a char** that has one space too much? problem ? if so check for that when you count the len and just -1 if its there.
				continue ; */
			else
				env[i] = ft_strdup(environ[i]);
		}
		env[i] = NULL;
	}
	return (env);
}

/* $>dasdads
$>retur
fail.
also
failed when i just gave wrong argument. */

void	init_msh(t_msh *msh)
{
	ft_printf("\n{blu}******************************************\n");
	ft_printf("\
	\t{yel}M{gre}I{red}N{blu}I{mag}S{blu}H{red}E{gre}L{yel}L{cya}\n");
	ft_printf("{blu}******************************************{nor}\n\n");
	msh->args = NULL;
	msh->paths = NULL;
	msh->cli = NULL;
	msh->env = get_env();
}

void	free_mem(t_msh *msh)
{
	if (msh->args)
		ft_arrfree(msh->args, ft_arrlen(msh->args));
	if (msh->paths)
		ft_arrfree(msh->paths, ft_arrlen(msh->paths));
	ft_strdel(&msh->cli);
}
