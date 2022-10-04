/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/03 11:13:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "libft.h"
/* need printf? */
# include "ft_printf.h"
# include "get_next_line.h"
/* need vectors? */
# include "vec.h"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
/* for lstat */
# include <sys/stat.h>
//for linux
/* # include <sys/wait.h>
# include <sys/types.h> */

# define MSH_TOK_BUFSIZE 64
# define MAX_PATHLEN 1024

typedef struct s_msh
{
	char	**args;
	char	**env;
	char	**paths;
	char	*cl;
}			t_msh;

/*
**	Function Declarations for builtin shell commands:
*/
int		msh_cd(t_msh *msh);
int		msh_echo(t_msh *msh);
int		msh_pwd(t_msh *msh);
int		msh_env(t_msh *msh);
int		msh_setenv(t_msh *msh);
int		msh_unsetenv(t_msh *msh);
int		msh_exit(t_msh *msh);

/* Init and free */
void	free_mem(t_msh *msh);
void	init_msh(t_msh *msh);

/* Parser */

void	split_args(t_msh *msh, char **cl);
void	change_variables(t_msh *msh);

/* From main */
int		parser(t_msh *msh);
int		msh_launch(t_msh *msh);

/* Change envirionment variables */
char	*get_env_value(char **env, char *var);
char	**update_env_var(t_msh *msh);
char	**update_pwd(t_msh *msh, char *oldcwd);
char	**set_env_var(char **env, char *key, char *value);
char	**unset_env_var(char **env, char *key);

/* Tools */
char	*extract_key(char *key_value);

typedef int			(*t_fptr)(t_msh *msh);

static const char	*g_builtin_str[] = {
	"cd",
	"echo",
	"pwd",
	"env",
	"setenv",
	"unsetenv",
	"exit"
};

static const t_fptr	g_builtin_func[] = {
	&msh_cd,
	&msh_echo,
	&msh_pwd,
	&msh_env,
	&msh_setenv,
	&msh_unsetenv,
	&msh_exit
};

#endif
