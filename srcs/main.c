/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 10:51:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static size_t	num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

static int	exec_args(t_msh *msh)
{
	size_t	i;

	if (!msh->args[0])
		return (1);
	i = 0;
	while (i < num_builtins())
	{
		if (!ft_strcmp(msh->args[0], g_builtin_str[i]))
			return (g_builtin_func[i](msh));
		i++;
	}
	return (msh_launch(msh));
}

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
	while ((token = ft_strsep(&cli, delimit)) != NULL)
		tokens[i++] = ft_strdup(token);
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
		if (get_next_line(STDIN_FILENO, &msh.cli) == 1)
		{
			msh.args = split_tokens(msh.cli, " \t\n");
			status = exec_args(&msh);
			msh.env = update_env_var(&msh);
		}
		else
			ft_putstr_fd("minishell: could not read input\n", STDERR_FILENO);
		free_mem(&msh);
	}
	if (msh.env)
		ft_arrfree(msh.env, ft_arrlen(msh.env));
	return (0);
}
