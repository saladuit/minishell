#include <expander.h>

int32_t	check_expand(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int32_t	is_double_quoted(char *str)
{
	if (*str == '\"')
	{
		if (str[ft_strlen(str) - 1] == '\"')
			return (1);
	}
	return (0);
}

int32_t	is_single_quoted(char *str)
{
	if (*str == '\'')
	{
		if (str[ft_strlen(str) - 1] == '\'')
			return (1);
	}
	return (0);
}

char	*strjoin_free_free(char *expanded, char *tmp)
{
	expanded = ft_strjoin_free(expanded, tmp);
	free(tmp);
	return (expanded);
}
