#include "libft.h"
#include <lexer.h>
#include <message.h>
#include <stdbool.h>
// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, I/O redirectors, and semicolons.

// Delimiters ";", "|", "&".

bool	is_quotechar(const char c)
{
	if (c == '\"' || c == '\'')
	{
		return (true);
	}
	return (false);
}

int32_t	is_tokenchar(const char *str)
{
	if (*str == '|')
		return (1);
	else if (*str == '<' || *str == '>')
	{
		if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
			return (2);
		return (1);
	}
	return (0);
}

void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input))
		(*input)++;
}
int32_t	find_next_quote(const char *command_line, char c)
{
	size_t	i;

	i = 1;
	while (command_line[i] != c && command_line[i])
		i++;
	return (i);
}
size_t	get_token_len(const char *command_line)
{
	size_t	i;

	i = 0;
	if (is_tokenchar(&command_line[i]))
		return (is_tokenchar(&command_line[i]));
	while (command_line[i] && !ft_iswhitespace(command_line[i]) && \
			!is_tokenchar(&command_line[i]))
	{
		if (is_quotechar(command_line[i]))
		{
			i += find_next_quote(&command_line[i], command_line[i]);
		}
		i++;
	}
	return (i);
}

char	*make_token(const char **command_line)
{
	char	*symbol;
	size_t	token_len;

	token_len = get_token_len(*command_line);
	symbol = ft_substr(*command_line, 0, token_len);
	if (!symbol)
		return (NULL);
	*command_line += token_len;
	return (symbol);
}

int32_t	lexer(const char *command_line, t_list **tokens)
{
	t_list	*node;

	*tokens = NULL;
	while (*command_line)
	{
		ft_skip_whitespaces(&command_line);
		if (*command_line)
		{
			node = ft_lstnew(make_token(&command_line));
			if (!node)
				return (ERROR);
			ft_lstadd_back(tokens, node);
		}
	}
	return (SUCCESS);
}
