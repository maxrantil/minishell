#include <msh.h>

char	*get_env_var(char **env, char *var)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
		{
			ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(env[i] - 5));
			ft_strcpy(ret, ft_strchr(env[i], '/'));
			return (ret);
		}
		i++;
	}
	return (NULL);
}