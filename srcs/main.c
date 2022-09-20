/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/19 18:19:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
**	List of builtin commands, followed by their corresponding functions.
*/

char	*builtin_str[] = {
	"cd",
	"echo",
	"pwd",
	"env",
	"exit"
};


//fix echo
int	(*builtin_func[]) (t_msh *msh) = {
	&msh_cd,
	&msh_echo,
	&msh_pwd,
	&msh_env,
	&msh_exit
};

int	check_paths(t_msh *msh)
{
	char	*path;
	size_t	i;
	size_t	j;

	i = 0;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PATH=", 5))
		{
			msh->paths = (char **)ft_memalloc(sizeof(char *) * MSH_TOK_BUFSIZE);
			j = 0;
			while ((path = ft_strsep(&msh->env[i], ":")) != NULL)
				msh->paths[j++] = ft_strchr(path, '/');
			return (1);
		}
		i++;
	}
	return (0);
}

// void prints_paths(t_msh *msh)
// {
// 	int i = 0;

// 	while (msh->paths[i])
// 		ft_printf("%s\n", msh->paths[i++]);
// }

char	*verify_arg(t_msh *msh)	//fix for if the full path is given and not only the arg
{
	struct stat	statbuf;
	char		*verify;
	size_t		i;

	i = 0;
	while (msh->paths[i])
	{
		verify = (char *)ft_memalloc(sizeof(char) * MAX_PATHLEN);
		// ft_bzero(verify, MAX_PATHLEN);
		ft_strcat(verify, msh->paths[i]);
		ft_strcat(verify, "/");
		ft_strcat(verify, msh->args[0]);
		if (!lstat(verify, &statbuf))
			return (verify);
		free(verify);
		i++;
	}
	return (NULL);
}

/* child pid = 0 */
int	msh_launch(t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	check_paths(msh);
	// prints_paths(msh);
	if (pid == 0)
	{
		execve(msh->args[0], msh->args, NULL);
		execve(verify_arg(msh), msh->args, NULL);
		ft_printf("minishell: %s: ", msh->args[0]);
		ft_putstr_fd("command not found\n", STDERR_FILENO);
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
			return ((*builtin_func[i])(msh));
		i++;
	}
	return (msh_launch(msh));
}

char	**split_tokens(char *cli, char *delimit)
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
	while ((token = ft_strsep(&cli, delimit)) != NULL)
	{
		if (ft_strlen(token))
			tokens[i++] = token;
	}
	return (tokens);
}

int	main(void)
{
	t_msh	msh;
	int		status;
	
	init_msh(&msh);
	status = 1;
	while (status)
	{
		ft_printf("{yel}${gre}>{nor} ");
		// msh.cli = NULL;
		if (get_next_line(STDIN_FILENO, &msh.cli) == 1)// && msh.cli[0])
		{
			msh.args = split_tokens(msh.cli, " \t\n\v\f\r");
			status = exec_args(&msh);
		}
		else
			ft_putstr_fd("minishell: could not read input\n", STDERR_FILENO);
		free_mem(&msh);
	}
	return (0);
}
