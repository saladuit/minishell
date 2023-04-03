#include <minishell.h>

bool	is_quotechar(const char c)
{
	if (c == '\"' || c == '\'')
	{
		return (true);
	}
	return (false);
}
