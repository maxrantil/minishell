/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/12 18:33:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	List of builtin commands, followed by their corresponding functions.
*/

char *builtin_str[] = {
  "cd",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &msh_cd,
  &msh_exit
};

int msh_cd(char **args)
{
	if (!args[1])
		ft_putstr_fd("./minishell: expected argument to \"cd\"\n", STDERR_FILENO);
	else
	{
		if (chdir(args[1]) != 0) {
      	{
			ft_putstr_fd("error: could not change directory", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
    }
  }
  return 1;
}

int msh_exit(char **args)
{
	if (*args)
		return (0);
	return (1);
}

/* child pid = 0 */
int	msh_launch(t_msh *msh)
{
	pid_t	pid;
	// extern char	**environ;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		// if (execve(args[0], args, NULL) == -1)
		if (execvp(msh->args[0], msh->args) == -1)
			ft_putstr_fd("error: execve failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("error: pid failed\n", STDERR_FILENO);
	else
		waitpid(pid, &status, WUNTRACED);
	return (1);
}

static size_t num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

int	exec_args(t_msh *msh)
{
	size_t	i;

	if (!msh->args[0])
		return (1);
	i = 0;
	while (i < num_builtins())
	{
		if (!ft_strcmp(msh->args[0], builtin_str[i]))
			return ((*builtin_func[i])(msh->args));
		i++;
	}
	return (msh_launch(msh));
}

/* int	check_whitespace(char *str)
{
	while (*str)
	{
		if (ft_isspace(str))
			return (1);
		str++;
	}
	return (0);
} */

char	**split_tokens(char *cli, char *delimit)
{
	char	**tokens;
	char	*token;
	size_t	i;

	tokens = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
	if (!tokens)
	{
		ft_putstr_fd("error: malloc tokens", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while ((token = ft_strsep(&cli, delimit)) != NULL)
		tokens[i++] = token;
	return (tokens);
}

int	main(void)
{
	t_msh	msh;
	int		status;
	int		line;

	init_msh(&msh);
	status = 1;
	while (status)
	{
		ft_putstr(PROMPT);
		line = get_next_line(STDIN_FILENO, &msh.cli);
		if (line == 1 && msh.cli[0])
		{
			msh.args = split_tokens(msh.cli, " \t\r\n\a");
			status = exec_args(&msh);
		}
		for (int i = 0; msh.args[i] != NULL; i++)
			ft_printf("%s\n", msh.args[i]);
		// free_mem(&msh);
	}
	return (0);
}
