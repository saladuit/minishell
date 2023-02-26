#include <minishell.h>

bool	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}
