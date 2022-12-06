#include <minishell.h>

bool	valid_varchar(char c)
{
	return (!ft_iswhitespace(c) && !is_quote(c) && c);
}

int32_t	check_expand(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char	*strjoin_free_free(char *expanded, char *tmp)
{
	expanded = ft_strjoin_free(expanded, tmp);
	free(tmp);
	return (expanded);
}
