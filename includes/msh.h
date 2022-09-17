#ifndef MSH_H
# define MSH_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
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

void	free_mem(char **args, char *cli);
/*
**	Function Declarations for builtin shell commands:
*/
int msh_cd(char **args);
int msh_exit(char **args);

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


#endif