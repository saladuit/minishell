#include <minishell.h>

void pair_clean(t_pair *pair)
{
	if (pair->key)
		free(pair->key);
	if (pair->value)
		free(pair->value);
	if (pair)
		free(pair);
}

char	*pair_to_str(t_pair *pair)
{
	char	*str;
	size_t	length;

	length = ft_strlen(pair->key) + ft_strlen(pair->value) + 2;
	str = ft_calloc(length, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, pair->key, length);
	ft_strlcat(str, "=", length);
	ft_strlcat(str, pair->value, length);
	return (str);
}
