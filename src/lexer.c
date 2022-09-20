#include <lexer.h>
#include <message.h>
#include <stdio.h> // Remove
// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, I/O redirectors, and semicolons.

// Delimiters ";", "|", "&".

int32_t	is_quotechar(char c)
{
	if (c == '\"' || c == '\'')
	{
		return (1);
	}
	return (0);
}

int32_t	is_tokenchar(char c)
{
	if (c == '|' || c == '<' || c == '>')
	{
		return (1);
	}
	return (0);
}

void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input) && **input)
		(*input)++;
}

int32_t	get_token_len(const char *command_line)
{
	int32_t	i;
	int32_t	quoted;

	i = 0;
	quoted = 0;
	if (is_tokenchar(command_line[i]))
		return (1);
	while ((!ft_iswhitespace(command_line[i]) || quoted) && command_line[i])
	{
		if (is_quotechar(command_line[i]) && !quoted)
			quoted = command_line[i];
		else if (is_tokenchar(command_line[i]) && !quoted)
			break ;
		else if (is_quotechar(command_line[i]) && quoted == command_line[i])
			quoted = 0;
		i++;
	}
	return (i);
}

char	*make_token(const char **command_line)
{
	char	*symbol;
	int32_t	token_len;

	token_len = get_token_len(*command_line);
	symbol = ft_calloc(token_len + 1, sizeof(char));
	if (!symbol)
		return (NULL);
	ft_strlcpy(symbol, *command_line, token_len + 1);
	*command_line += token_len;
	return (symbol);
}

int32_t	lexer(const char *command_line, t_list **tokens)
{
	t_list	*node;

	while (*command_line)
	{
		ft_skip_whitespaces(&command_line);
		node = ft_lstnew(make_token(&command_line));
		if (!node)
			return (ERROR);
		ft_lstadd_back(tokens, node);
	}
	return (SUCCESS);
}
