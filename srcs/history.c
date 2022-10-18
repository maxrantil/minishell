/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/18 13:59:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char	*get_home(char	*file)
{
    struct passwd	*pwd;
	uid_t			uid;
	
	uid = getuid();
    pwd = getpwuid(uid);
	if (!pwd)
	{
		ft_putendl_fd("error, cound not get home directory", 2);
		exit(EXIT_FAILURE);
	}
	file = ft_strjoin(pwd->pw_dir, "/.msh_history");
	return (file);
}

/*
**	O_CREAT If pathname does not exist, create it as a regular file.
**	O_WRONLY access modes: read/write
**	O_RDONLY access modes: read/write
**	S_IRUSR  00400 user has read permission 
**	S_IWUSR  00200 user has write permission	
**	S_IRGRP  00040 group has read permission	
**	S_IROTH  00004 others have read permission
*/

void	write_history_to_file(t_msh *msh)
{
	char	*file;
	size_t	cpy;
	int		fd;

	file = ft_strjoin(getenv("HOME"), "/.msh_history");
	if (!file)
		file = get_home(file);
	fd = open(file, O_WRONLY);
	if (fd)
	{
		cpy = 0;
		if (msh->v_history.len > 1024)
			cpy = msh->v_history.len % 1024;
		while (cpy < msh->v_history.len)
		{
			ft_putendl_fd((char *)vec_get(&msh->v_history, cpy), fd);
			cpy++;
		}
		close(fd);
	}
	ft_strdel(&file);
	return ;
}

void	get_history(t_msh *msh)
{
	char	*file;
	char	*buf;
	int		fd;

	vec_new(&msh->v_history, 0, sizeof(char) * 256);
	file = ft_strjoin(getenv("HOME"), "/.msh_history");
	if (!file)
		file = get_home(file);
	fd = open(file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&msh->v_history, buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
	ft_strdel(&file);
}

int	msh_history(t_msh *msh)
{
	size_t	num_incr;

	if (msh->cl[0] == '^')
		ft_printf("%s\n", (char *)vec_get(&msh->v_history, msh->v_history.len - ft_strlen(msh->cl)));
	else
	{
		num_incr = 0;
		while (num_incr <= msh->v_history.len)
		{
			ft_putnbr(num_incr + 1);
			write(1, "  ", 2);
			ft_putendl((char *)vec_get(&msh->v_history, num_incr));
			num_incr++;
		}
	}
	return (1);
}
