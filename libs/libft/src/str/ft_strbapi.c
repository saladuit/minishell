#include "libft.h"

bool	ft_strbapi(char const *s, bool (*f)(int))
{
	size_t	i;
	size_t	len;

	if ((s == 0) || (f == 0))
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}
