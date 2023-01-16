#include <minishell.h>

// str should start at a single quote. finds the next single quote and returns the lenght between the two.
int32_t	skip_single_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i + 1);
	}
	return (i);
}

// str should start at a double quote. finds the next double quote and returns the lenght between the two.
int32_t	skip_double_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\"')
			return (i + 1);
	}
	return (0);
}

// Skip the variables name. returns the length of the variable name that the string starts with.
int32_t	skip_variable_name(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '?')
			return (i + 1);
	}
	else if (str[i] == '~')
		return (i + 1);
	while (valid_varchar(str[i]))
		i++;
	return (i);
}

// Skip whitespace. return the length of whitespace.
int32_t	skip_whitespace(char *str)
{
	int32_t	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	return (i);
}

// state 0 is no quotes, 1 is double, 2 is single. 2 is never used.
int32_t	find_var_start(char *str, int32_t index)
{
	int32_t	i;
	int32_t	quoted;

	i = 0;
	quoted = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '\'' && quoted == 0)
			i += skip_single_quotes(&str[i]);
		else if (str[i] == '\"')
			quoted = (quoted - 1) * -1;
		i++;
	}
	while (str[i] != '$' && str[i] != '~' && str[i])
	{
		if (str[i] == '\'' && quoted == 0)
			i += skip_single_quotes(&str[i]);
		else if (str[i] == '\"')
			quoted = (quoted - 1) * -1;
		i++;
	}
	return (i);
}
