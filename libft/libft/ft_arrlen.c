#include "libft.h"

size_t	ft_arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}