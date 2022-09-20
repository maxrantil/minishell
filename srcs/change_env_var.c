#include "msh.h"

char	*change_shlvl(char *shlvl)
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

static void	change_pwd(char ** env, size_t i)
{
	char		cwd[MAX_PATHLEN];
	char 		*pwd;
	static int	st;

	getcwd(cwd, sizeof(cwd));
	if (st)
		free(env[i]);
	st++;
	if (st == 0)
		st = 1;
	pwd = ft_strnew(4 + ft_strlen(cwd));
	ft_strcpy(pwd, "PWD=");
	ft_strcat(pwd, cwd);
	env[i] = pwd;
}

static void	change_oldpwd(char **env, size_t i)
{
	static int	st;
	size_t		j;

	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(env[j], "OLDPWD=", 7))
		{
			if (st)
				free(env[j]);
			st++;
			if (st == 0)
				st = 1;
			env[j] = ft_strjoin("OLDPWD=", ft_strchr(env[i], '/'));
		}
		j++;
	}
}

void	update_pwd(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			change_oldpwd(env, i);
			change_pwd(env, i);
		}
		i++;
	}
}