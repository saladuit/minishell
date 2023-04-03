#include <minishell.h>

void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input))
		(*input)++;
}
