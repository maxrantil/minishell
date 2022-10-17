#include "msh.h"

static 	void	write_to_history(t_msh *msh)
{
	int		fd;

	fd = open(".msh_history", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd > 0)
		ft_putendl_fd(msh->cl, fd);
	close(fd);
}

static void	print_history()
{
	char	*buf;
	int		fd;

	fd = open(".msh_history", O_RDONLY);
	while (get_next_line(fd, &buf) > 0)
	{
		ft_putendl(buf);
		ft_strdel(&buf);
	}
	close(fd);
}

static size_t	history_count()
{
	char	*buf;
	size_t	line_numbers;
	int		fd;

	fd = open(".msh_history", O_RDONLY);
	line_numbers = 0;
	while (get_next_line(fd, &buf) > 0)
	{
		line_numbers++;
		ft_strdel(&buf);
	}
	close(fd);
	return (line_numbers);
}

static void	print_history_of_choice(size_t line_numbers, size_t line)
{
	char	*buf;
	int		fd;

	fd = open(".msh_history", O_RDONLY);
	line = line_numbers - line;
	while (get_next_line(fd, &buf) > 0)
	{
		--line;
		if (!line)
			break ;
		ft_strdel(&buf);
		
	}
	ft_putendl(buf);
	ft_strdel(&buf);
	close(fd);
}

/*
**	O_CREAT If pathname does not exist, create it as a regular file.
**	O_RDWR access modes: read/write
**	O_APPEND The  file  is  opened  in append mode.
**	S_IRWXU  00700 user (file owner) has read, write, and execute permissionS_IRUSR  00400 user has read permission	
*/
void	history(t_msh *msh, int status)
{
	if (status == 1 && msh->cl[0] == 'h' && msh->cl[1] == 'i' && msh->cl[2] == 's' && msh->cl[3] == 't' && msh->cl[4] == 'o' && msh->cl[5] == 'r' && msh->cl[6] == 'y')
		print_history();
	else if (status == 1 && msh->cl[0] == '^')
		print_history_of_choice(history_count(), ft_strlen(msh->cl) - 1);
	else if (status == 2)
		write_to_history(msh);
}