#include <minishell.h>

int32_t	is_tokenchar(const char *str)
{
	char c;

	c = *str;
	if (is_pipe(c))
		return (1);
	else if (c == '<' || c == '>')
	{
		if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
			return (2);
		return (1);
	}
	return (0);
}
