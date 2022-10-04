#include "msh.h"

static int	get_tilde(t_msh *msh, char **tilde, size_t i)
{
	if (msh->args[i][1] == '-')
	{
		*tilde = get_env_value(msh->env, "OLDPWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else if (msh->args[i][1] == '+')
	{
		*tilde = get_env_value(msh->env, "PWD=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 2);
	}
	else
	{
		*tilde = get_env_value(msh->env, "HOME=");
		if (!*tilde)
			return (0);
		*tilde = ft_strupdate(*tilde, msh->args[i] + 1);
	}
	return (1);
}

static char	*save_begin(t_msh *msh, size_t j)
{
	char	*begin_arg;
	size_t	len;

	len = ft_strclen(msh->args[j], '$');
	if (len)
	{
		begin_arg = ft_strsub(msh->args[j], 0, len);
		return (begin_arg);
	}
	return (NULL);
}

static char	*get_new_arg(t_msh *msh, char **dollars)
{
	char	*key;
	char	*new_arg;
	char	*temp;
	size_t	i;
	size_t	j;

	j = 0;
	new_arg = NULL;
	while (dollars[j])
	{
		key = ft_strdup(dollars[j]);
		key = ft_strupdate(key, "=");
		i = 0;
		while (msh->env[i])
		{
			if (!ft_strncmp(msh->env[i], key, ft_strlen(key)))
			{
				if (!new_arg)
					new_arg = ft_strnew(1);
				temp = ft_strdup(ft_strchr(msh->env[i], '=') + 1);
				new_arg = ft_strupdate(new_arg, temp);
				ft_strdel(&temp);
				break ;
			}
			i++;
		}
		ft_strdel(&key);
		j++;
	}
	ft_arrfree((void **)dollars, ft_arrlen((void *)dollars));
	ft_memdel((void *)&dollars);
	return (new_arg);
}

static void	get_dollar(t_msh *msh, char *dollar, size_t i)
{
	char	**dollars;
	char	*new_arg;
	char	*begin_arg;

	begin_arg = save_begin(msh, i);
	dollars = ft_strsplit(dollar, '$');
	new_arg = get_new_arg(msh, dollars);
	if (begin_arg)
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_strupdate(begin_arg, new_arg);
	}
	else if (new_arg)
	{
		ft_strdel(&msh->args[i]);
		msh->args[i] = ft_strdup(new_arg);	
	}
	else
		ft_memset((void *)msh->args[i], '\0', ft_strlen(msh->args[i]));
	ft_strdel(&new_arg);
}

static	size_t	check_tilde(char *str)
{
	size_t	i;

	i = 1;
	if (!str[i])
		return (1);
	if ((str[i] == '+' || str[i]== '-') && !str[i + 1])
		return (1);
	return (0);
}

void	change_variables(t_msh *msh)
{
	char	*tilde;
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen((void **)msh->args);
	i = 1;
	while (i < arrlen)
	{
		j = 0;
		if (msh->args[i])
		{
			while (msh->args[i][j] != '\0')
			{
				if (msh->args[i][0] == '~')
				{
					if (check_tilde(msh->args[i]))
					{
						if (get_tilde(msh, &tilde, i)) 
						{
							ft_strdel(&msh->args[i]);
							msh->args[i] = tilde;
						}
					}
				}
				else if (msh->args[i][j] == '$' && (msh->args[i][j + 1] == '_' || ft_isalpha(msh->args[i][j + 1]))) //ft_isascii as second parameter?
					get_dollar(msh, ft_strchr(msh->args[i], '$'), i);
				else if (msh->args[i][j] == '$' && msh->args[i][j + 1] == '$') //bonus fun, works alone but not if you append to end of another $variable
				{
					ft_strdel(&msh->args[i]);
					msh->args[i] = ft_itoa(getpid());
				}
				j++;
			}
		}
		i++;
	}
}