#include "msh.h"

static size_t	count_quotes(char *cli)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (cli[i] != '\n' && cli[i] != '\0')
	{
		if (cli[i] == '\"')
		{
			if (i == 0 || cli[i] != '\\')
				++count;
		}	
		i++;
	}
	return (count);
}

static int	check_quotes(char **cli)
{
	size_t	count;
	
	if (*cli)
	{
		count = count_quotes(*cli);
		if (count % 2 != 0)
		{
			ft_putstr_fd("error, double quotes don't match.\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

static void	trim_cli(char **cli)
{
	char *trimmed;

	trimmed = ft_strtrim(*cli);
	free(*cli);
	*cli = trimmed;
}

/* static void	trim_arg(char **cli)
{
	char *trimmed;

	trimmed = ft_strtrim(ft_strchr(*cli, ' '));
	free(*cli);
	*cli = trimmed;
} */

static char	**split_tokens(char *cli, char *delimit)
{
	char	**tokens;
	char	*token;
	size_t	i;

	tokens = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
	if (!tokens)
	{
		ft_putstr_fd("error: malloc tokens\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 0;
	token = ft_strsep(&cli, delimit);
	while (token)
	{
		ft_printf("token [%s]\n", token);
		tokens[i++] = ft_strdup(token);
		token = ft_strsep(&cli, delimit);
	}
	return (tokens);
}

int	parser(t_msh *msh)
{
	if (!check_quotes(&msh->cli))
		return (0);
	trim_cli(&msh->cli);
	//need to split spaces between arg0 and arg1
	msh->args = split_tokens(msh->cli, " \t");
	return (1);
}	