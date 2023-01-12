#include <minishell.h>

// counts the amount of splits needed for the str. counting quoted areas as a single word.
static int32_t	split_count(char *str)
{
	int32_t	i;

	i = 0;
	if (!str)
		return (i);
	while (*str)
	{
		str += skip_whitespace(str);
		if (*str)
			i++;
		while (*str && !ft_iswhitespace(*str))
		{
			if (*str == '\"')
				str += skip_double_quotes(str);
			else if (*str == '\'')
				str += skip_single_quotes(str);
			else
				str++;
		}
	}
	return (i);
}

// Finds the length and size of a word in regards to quotes and returns a newly allocated string using ft_substring.
static char	*get_word(char *str)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (!ft_iswhitespace(str[word_len]) && str[word_len])
	{
		if (str[word_len] == '\"')
			word_len += skip_double_quotes(&str[word_len]);
		else if (str[word_len] == '\'')
			word_len += skip_single_quotes(&str[word_len]);
		else
			word_len++;
	}
	word = ft_substr(str, 0, word_len);
	if (!word)
		return (NULL);
	return (word);
}

// Split words / sections based on whitespace. quoted words / sections do not get split.
char	**split_words(char *str)
{
	int32_t	i;
	int32_t	j;
	int32_t	count;
	char	**split;

	i = 0;
	j = 0;
	count = split_count(str);
	split = malloc((count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (str[i])
	{
		i += skip_whitespace(&str[i]);
		if (str[i])
		{
			split[j] = get_word(&str[i]);
			i += ft_strlen(split[j]);
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}
