#include "msh.h"

unsigned int hash_function(char *program)
{
	unsigned int	hash;
	int 			c;

	hash = 0;
	while (c = *program++)
		hash = c + (hash << 6) + (hash << 16) - hash;
	return (hash % HASH_SIZE);
}

void	init_hash_table(t_builtin **ht)
{
	int i;

	i =	0;
	while (i < HASH_SIZE)
		ht[i++] = NULL;
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