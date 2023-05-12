#include <limits.h>

size_t	ft_array_len(char **args)
{
	size_t	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
