/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:35:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/26 13:58:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
**	It takes a string and returns an integer
**	@return The hash value of the program name.
*/
size_t hash_function(char *program)
{
	size_t	hash;
	int 	c;

	hash = 0;
	while ((c = *program++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (hash % HASH_SIZE);
}

/*
 * It takes a hash table and a pointer to a builtin, and inserts the builtin into the hash table
 */
static char	*ht_insert(t_builtin **ht, t_builtin *p)
{
	int index;
	
	if (!p)
		return (NULL);
	index = hash_function(p->program);
	p->next = ht[index];
	ht[index] = p;
	return (ht[index]->program);
}

/**
 * It creates a new t_builtin struct, initializes it with the given string and function pointer, and
 * inserts it into the hash table
 * 
 * @param ht the hash table
 * @param str The name of the builtin
 * @param f the function that will be called when the command is executed
 */
static void	init_ht_struct(t_builtin **ht, char *str, int (*f)(t_msh *msh))
{
	t_builtin	*new;

	new = (t_builtin *)ft_memalloc(sizeof(t_builtin));
	new->program = str;
	new->function = f;
	new->next = NULL;
	ht_insert(ht, new);
}

/**
 * It initializes the hash table
 * 
 * @param ht The hash table
 */
static void	init_ht(t_builtin **ht)
{
	int	i;

	i =	0;
	while (i < HASH_SIZE)
		ht[i++] = NULL;
}
	
/**
 * It initializes the hash table with the builtin functions
 * 
 * @param ht the hash table
 */
void initialize_ht(t_builtin **ht)
{
	init_ht(ht);
	init_ht_struct(ht, "cd", &msh_cd);
	init_ht_struct(ht, "echo", &msh_echo);
	init_ht_struct(ht, "env", &msh_env);
	init_ht_struct(ht, "exit", &msh_exit);
	init_ht_struct(ht, "setenv", &msh_setenv);
	init_ht_struct(ht, "unsetenv", &msh_unsetenv);
}
