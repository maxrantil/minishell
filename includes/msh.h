/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/12 16:45:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <dirent.h>
# include <sys/stat.h>

# define MAX_PATHLEN 1024

typedef struct s_msh
{
	char	**args;
	char	**env;
	char	**temp_env;
	char	**paths;
	char	*cl;
}			t_msh;


/* Function Declarations for builtin */
int		msh_cd(t_msh *msh);
int		msh_echo(t_msh *msh);
int		msh_env(t_msh *msh);
int		msh_setenv(t_msh *msh);
int		msh_unsetenv(t_msh *msh);
int		msh_exit(t_msh *msh);

/* Init and free */
void	init_msh(t_msh *msh);

/* Parser */
size_t	count_arguments(char *str);
char	**get_arguments(char *str, int argc);
void	strip_quotes(char **args);
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
void	get_dollar(t_msh *msh, char *dollar, size_t i);
void	tilde(t_msh *msh, size_t i);
void	loop_setenv(t_msh *msh, char *arg);

/* Tools */
/* int		check_address(char *addr); */
void	print_error(char *arg, int i);
char	*extract_key(char *key_value);
void	free_mem(t_msh *msh, ssize_t code);
int		find_matching_quote(char *str, char quote);

typedef int			(*t_fptr)(t_msh *msh);

static const char	*g_builtin_str[] = {
	"cd",
	"echo",
	"env",
	"setenv",
	"unsetenv",
	"exit"
};

static const t_fptr	g_builtin_func[] = {
	&msh_cd,
	&msh_echo,
	&msh_env,
	&msh_setenv,
	&msh_unsetenv,
	&msh_exit
};

#endif
