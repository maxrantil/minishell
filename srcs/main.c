/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/07 17:12:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"


static int	exec_args(t_msh *msh, t_builtin **ht)
{

	int i;

	if (!msh->args[0])
		return (1);
	i = 0;
	while (i < HASH_SIZE)
	{
		if (ft_strcmp(ht[i]->program, msh->args[0]) == 0)
		{
			return (ht[i]->function(msh));
		}
		i++;
	}
	return (msh_launch(msh));
}

unsigned int hash_function(char *program)
{
	unsigned int	hash;
	int 			c;

	hash = 0;
	while ((c = *program++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (hash % HASH_SIZE);
}

int	hash_table_insert(t_builtin **ht, t_builtin *p)
{
	int index;
	
	if (!p)
		return (0);
	index = hash_function(p->program);
	p->next = ht[index];
	ht[index] = p;
	return (1);
}

void	init_hash_table(t_builtin **ht)
{
	int i;

	i =	0;
	while (i < HASH_SIZE)
		ht[i++] = NULL;
}

int	main(void)
{
	t_msh		msh;
	t_builtin	*ht[HASH_SIZE];
	int			status;

	init_msh(&msh);
	init_hash_table(ht);
	t_builtin cd = {.program="cd", .function=&msh_cd};
	t_builtin env = {.program="env", .function=&msh_env};
	t_builtin echo = {.program="echo", .function=&msh_echo};
	t_builtin setenv = {.program="setenv", .function=&msh_setenv};
	t_builtin unsetenv = {.program="unsetenv", .function=&msh_unsetenv};
	if (hash_table_insert(ht, &cd)
	&& hash_table_insert(ht, &env)
	&& hash_table_insert(ht, &echo)
	&& hash_table_insert(ht, &setenv)
	&& hash_table_insert(ht, &unsetenv))
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
			free_mem(&msh, 1);
		}
		else
			ft_putstr_fd("minishell: could not read input\n", STDERR_FILENO);
	}
	free_mem(&msh, 2);
	return (0);
}
