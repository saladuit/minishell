#include <minishell.h>

bool	is_metachar(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2) || is_meta(*str))
		return (true);
	return (false);
}

size_t	metachar_len(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	else
		return (1);
}
