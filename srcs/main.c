/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/28 12:02:12 by mrantil          ###   ########.fr       */
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
			if (parser(&msh))
			{
				status = exec_args(&msh);
				msh.env = update_env_var(&msh);
			}
		}
		else
			ft_putstr_fd("minishell: could not read input\n", STDERR_FILENO);
		free_mem(&msh);
	}
	if (msh.env)
		ft_arrfree(msh.env, ft_arrlen(msh.env));
	return (0);
}
