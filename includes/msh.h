#ifndef MSH_H
# define MSH_H

# include "libft.h"
/* need printf? */
# include "ft_printf.h"
# include "get_next_line.h"
/* need vectors? */
# include "vec.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//for linux
#include <sys/wait.h>
#include <sys/types.h>

# define PROMPT "$> "
# define MSH_TOK_BUFSIZE 64

typedef struct s_msh
{
	char	**args;
}			t_msh;

/*
**	Function Declarations for builtin shell commands:
*/
int msh_cd(char **args);
int msh_exit(char **args);


void	free_mem(char **args);
void	init_msh(t_msh *msh);

#endif