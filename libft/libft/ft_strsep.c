#include "libft.h"

char	*ft_strsep(char **string_ptr, const char *delim)
{
	char	*begin;
	char	*end;

	begin = *string_ptr;
	if (begin == NULL)
		return NULL;
	end = begin + ft_strcspn(begin, delim);
	if (*end)
	{
		*end++ = '\0';
		*string_ptr = end;
	}
	else
	    *string_ptr = NULL;
	return (begin);
}