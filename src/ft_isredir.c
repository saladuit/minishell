#include <stdbool.h>

bool	ft_isredir(const char redir)
{
	if (redir == '>' || redir == '<')
		return (true);
	return (false);
}
