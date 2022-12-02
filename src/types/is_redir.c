#include <stdbool.h>

bool	is_redir(int c)
{
	return (c == '>' || c == '<');
}
