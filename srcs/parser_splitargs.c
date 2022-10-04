#include "msh.h"

static char *skip_whitespaces(char *ptr)
{
	while (ft_isspace((const char *)ptr))
		ptr++;
	return (ptr);
}

static int	count_arguments(char *cl)
{
	char	*p;
	int		quote;
	size_t	args;

    args = 0;
	p = cl;
    while (*p)
    {
		p = skip_whitespaces(p);
        if (*p == '"' || *p == '\'')
		{
            quote = *p++;
            while (*p && *p != quote)
				p++;
			args++;
            p++;
        }
        else if (*p)
		{
            while (*p && !ft_isspace((const char *)p) && *p != '"' && *p != '\'')
				p++;
			args++;
		}
    }
	ft_printf("arg count %d\n", args);
    return (args);
}

void	split_args(t_msh *msh, char **cl)
{
    char *p;
    char *p_check;
	char *begin;
    int count;
    int i;
	int quote;
	
	count = count_arguments(*cl);
	msh->args = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	if (!msh->args)
	{
		ft_putstr_fd("error: malloc args\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
    p = *cl;
	i = -1;
	while (++i < count)
	{
		p_check = p;
		p = skip_whitespaces(p);
		if (p_check != p && i > 1)
			msh->args[i - 1] = ft_strupdate(msh->args[i - 1], " ");
        if (*p == '"' || *p == '\'')
		{
            quote = *p++;
            begin = p;
            while (*p && *p != quote)
				p++;
			msh->args[i] = ft_strsub(begin, 0, p - begin);
            p++;
        }
        else if (*p)
		{
            begin = p;
            while (*p && !ft_isspace((const char *)p) && *p != '"' && *p != '\'')
				p++;
			msh->args[i] = ft_strsub(begin, 0, p - begin);
        }
		else
		{
			ft_putstr_fd("error, invalid argument\n", STDERR_FILENO);
			exit(1);
		}
    }
	msh->args[i] = NULL;
}