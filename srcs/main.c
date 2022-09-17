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

static void	free_array(void ***arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len)
	{
		if (*((*arr) + i))
		{
			free(*((*arr) + i));
			*((*arr) + i) = NULL;
		}
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static size_t	array_len(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	free_mem(char **args, char *cli)
{
	if (args)
		free_array((void ***)&args, array_len(args));
	if (cli)
		ft_strdel(&cli);
}

/* int main(int argc, char **argv, char **envp)
{
  for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);    
  }
  return 0;
} */

int msh_cd(char **args)
{
	if (!args[1])
		ft_printf("./minishell: expected argument to \"cd\"\n");
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
int	msh_launch(char **args)
{
	pid_t	pid;
	//pid_t 	wpid;
	// extern char	**environ;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		//if (execve(args[0], args, environ) == -1)
		if (execvp(args[0], args) == -1)
			ft_putstr_fd("error: execve failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("error: pid failed", STDERR_FILENO);
	else
	{
		do				//switch it up;
		{
			// wpid = waitpid(pid, &status, WUNTRACED);
			waitpid(pid, &status, WUNTRACED);
		} 
		while (!WIFEXITED(status) && !WIFSIGNALED(status));	
	}
	return (1);
}

static int num_builtins()
{
  return (sizeof(builtin_str) / sizeof(char *));
}

int	msh_exec(char **args)
{
	int	i;

	if (!args[0])
		return (1);
	i = 0;
	while (i < num_builtins())
	{
		if (!ft_strcmp(args[0], builtin_str[i]))
			return ((*builtin_func[i])(args));
		i++;
	}
	return (msh_launch(args));
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

char	**split_cli(char *cli)
{
	char	**tokens;

	tokens = ft_strsplit(cli, ' '); //how to i use all whitespaces as delimiter? ft_isspace somehow?
	return (tokens);
}

int	main(void)
{
	char	*cli;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr(PROMPT);
		if (get_next_line(STDIN_FILENO, &cli) && cli[0])
		{
			ft_printf("YES!\n");
			ft_printf("%s\n", cli);
			args = split_cli(cli);
			// ft_printf("%s\n", args[2]);
			status = msh_exec(args);
		}
		free_mem(args, cli);
	}
	return (0);
}
