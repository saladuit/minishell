#include <minishell.h>

// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, I/O redirectors, and semicolons.

// Delimiters ";", "|", "&".

// DO some tests
#include <stddef.h>

static int	ms_strcmp(const char *command, char *cmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (command[i] && cmp[j])
	{
		while (command[i] && command[i] == ' ')
			i++;
		while (cmp[j] && cmp[j] == ' ')
			j++;
		if (command[i++] != cmp[j++])
			return (0);
	}
	while (command[i])
	{
		if (command[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

// -- ERROR MESSAGES --
// | should give: "bash: syntax error near unexpected token `|'"
// <, >, <<,
// >> should give: "bash: syntax error near unexpected token `newline'"
// || should give: "bash: syntax error near unexpected token `||'"
// >> > should give: "bash: syntax error near unexpected token `>'"
// << < should give: "bash: syntax error near unexpected token `<'"
// $ $ and $ $SHLVL should give: "bash: $: command not found"
static bool	check_command(const char *command, t_status *exit)
{
	if (ms_strcmp(command, "|") == NOT_FOUND)
		return (*exit = message_general_error(E_UNEXPECTED_TOKEN, "|"), false);
	else if (ms_strcmp(command, "||") == NOT_FOUND)
		return (*exit = message_general_error(E_UNEXPECTED_TOKEN, "||"), false);
	else if (ms_strcmp(command, "<") == NOT_FOUND || ms_strcmp(command,
			"<<") == NOT_FOUND || ms_strcmp(command, ">") == NOT_FOUND
		|| ms_strcmp(command, ">>") == NOT_FOUND || ms_strcmp(command, "!"))
		return (*exit = message_general_error(E_UNEXPECTED_TOKEN, "newline"), false);
	else if (ms_strcmp(command, ">> >") == NOT_FOUND || ms_strcmp(command,
			"<< >") == NOT_FOUND)
		return (*exit = message_general_error(E_UNEXPECTED_TOKEN, ">"), false);
	else if (ms_strcmp(command, "<< <") == NOT_FOUND || ms_strcmp(command,
			">> <") == NOT_FOUND)
		return (*exit = message_general_error(E_UNEXPECTED_TOKEN, "<"), false);
	return (true);
}

void	print_tokens(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("[%s]\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

// returns true if the count of quotes (' or ") is even
// applied on the first found quote in the string
bool	are_quotes_closed(const char *str)
{
	size_t	count;
	size_t	i;
	int		quote;
	char	c;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && !quote)
		{
			c = str[i];
			quote = 1;
		}
		if (str[i] == c && quote)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (true);
	return (false);
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
	{
		message_system_call_error("make_token");
		return (NULL);
	}
	*command_line += token_len;
	return (symbol);
}

t_list	*lexer(const char *command_line, t_status *exit)
{
	t_list	*node;
	t_list	*tokens;
	char	*token;

	if (check_command(command_line, exit) == false)
		return (NULL);
	tokens = NULL;
	while (*command_line)
	{
		ft_skip_whitespaces(&command_line);
		if (are_quotes_closed(command_line) == false)
			return (*exit = message_general_error(E_QUOTES, command_line), NULL);
		if (*command_line)
		{
			token = make_token(&command_line);
			if (!token)
			{
				*exit = message_system_call_error("lexer");
				return (NULL);
			}
			node = ft_lstnew(token);
			if (!node)
			{
				*exit = message_system_call_error("lexer");
				free(token);
				return (NULL);
			}
			ft_lstadd_back(&tokens, node);
		}
	}
	return (tokens);
}
