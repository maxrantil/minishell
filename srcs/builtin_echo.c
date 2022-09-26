#include "msh.h"

static void	print_dollar(char **env, char *dollar)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], dollar, ft_strlen(dollar)))
			ft_printf("%s", ft_strchr(env[i], '=') + 1);
		i++;
	}
}

static void print_echo(t_msh *msh)
{
	size_t	arrlen;
	size_t	i;
	size_t	j;

	arrlen = ft_arrlen(msh->args) - 1;
	i = 1;
	while (i <= arrlen)
	{
		j = 0;
		while (msh->args[i][j])
		{
			if (msh->args[i][0] == '$')
			{
				print_dollar(msh->env, ft_strchr(msh->args[i], '$') + 1);
				break ;
			}
			else if (msh->args[i][j] != '\"')
				write(1, &msh->args[i][j], 1);
			j++;
		}
		if (i != arrlen)
			ft_putchar(' ');
		i++;
	}
}

static size_t	count_strings(char **args)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\"')
				++count;
			j++;
		}
		i++;
	}
	return (count);
}

int	msh_echo(t_msh *msh)
{
	size_t	count;

	count = count_strings(msh->args);
	if (count % 2 != 0)
	{
		ft_putstr_fd("error, double quotes don't match\n", STDERR_FILENO);
		return (2);
	}
	print_echo(msh);
	ft_putchar('\n');
	return (1);
}
