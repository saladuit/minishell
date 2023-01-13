#include <minishell.h>

bool	is_double_quoted(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] != '\"' && str[i])
		i++;
	i++;
	while (str[i] != '\"' && str[i])
		i++;
	return (str[i] == '\"');
}
