#include <minishell.h>

bool	is_meta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_metas(const char *str)
{
	int	a;

	if (is_meta(str[0]))
	{
		a = str[0];
		if (str[1] == a)
			return (true);
	}
	return (false);
}
