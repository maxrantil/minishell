/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2022/09/19 16:07:06 by mrantil          ###   ########.fr       */
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
//for linux
# include <sys/wait.h>
# include <sys/types.h>
/* for lstat */
#include <sys/stat.h>

# define MSH_TOK_BUFSIZE 64
# define MAX_PATHLEN 1024


typedef struct s_msh
{
	char	**args;
	char	**env;
	char	**paths;
	char	*cli;
}			t_msh;

/*
**	Function Declarations for builtin shell commands:
*/
int		msh_cd(t_msh *msh);
int		msh_pwd(t_msh *msh);
int		msh_env(t_msh *msh);
int		msh_exit(t_msh *msh);


void	free_mem(t_msh *msh);
void	init_msh(t_msh *msh);

#endif