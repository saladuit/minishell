#include <stdbool.h>

bool	ft_isdelimiter(const char sep)
{
	if (sep == '|')
		return (true);
	return (false);
}
