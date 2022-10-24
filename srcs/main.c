/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/24 15:38:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	exec_args(t_msh *msh, t_builtin **ht)
{
	t_builtin	*tmp;
	int			index;

	if (!msh->args[0])
		return (1);
	index = hash_function(msh->args[0]);
	tmp = ht[index];
	while (tmp)
	{
		if (ft_strcmp(msh->args[0], tmp->program) == 0)
			return (tmp->function(msh));
		tmp = tmp->next;
	}
	return (msh_launch(msh));
}

int	main(void)
{
	t_msh		msh;
	t_builtin	*ht[HASH_SIZE];
	int			status;

	init_msh(&msh);
	initialize_ht(ht);
	status = 1;
	while (status)
	{
		ft_printf("{yel}${gre}>{nor} ");
		if (get_next_line(STDIN_FILENO, &msh.cl) == 1)
		{
			status = parser(&msh);
			if (status > 0)
			{
				status = exec_args(&msh, ht);
				msh.env = update_env_var(&msh);
			}
			free_mem(&msh, ht, 1);
		}
		else
			ft_putstr_fd("minishell: could not read input\n", STDERR_FILENO);
	}
	free_mem(&msh, ht, 2);
	return (0);
}
