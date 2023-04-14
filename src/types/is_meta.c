#include <minishell.h>

bool	is_meta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}
