/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:28:44 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:28:46 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// returns true if the count of quotes (' or ") is even
// applied on the first found quote in the string
static bool	are_quotes_closed(const char *str)
{
	size_t	count;
	size_t	i;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && !quote)
		{
			quote = str[i];
			count++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			count++;
		}
		i++;
	}
	if (count % 2 == 0)
		return (true);
	return (false);
}

static size_t	get_token_len(const char *command_line)
{
	size_t	next_quote;
	size_t	i;

	i = 0;
	if (is_metachar(&command_line[i]))
		return (metachar_len(&command_line[i]));
	while (command_line[i] && !ft_iswhitespace(command_line[i])
		&& !is_metachar(&command_line[i]))
	{
		if (is_quote(command_line[i]))
		{
			next_quote = i + 1;
			while (command_line[next_quote] != command_line[i]
				&& command_line[next_quote])
				next_quote++;
			i = next_quote;
		}
		i++;
	}
	return (i);
}

static char	*make_token(const char **command_line, t_status *exit)
{
	char	*symbol;
	size_t	token_len;

	token_len = get_token_len(*command_line);
	symbol = ft_substr(*command_line, 0, token_len);
	if (!symbol)
	{
		*exit = message_system_call_error("make_token");
		return (NULL);
	}
	*command_line += token_len;
	return (symbol);
}

static t_list	*create_token_node(const char **command_line,
									t_status *exit, t_lexer *lex)
{
	t_list		*node;
	char		*token;

	token = make_token(command_line, exit);
	if (!token)
	{
		*exit = message_system_call_error("lexer");
		return (NULL);
	}
	if (lex->token_count != 0 && !check_meta_conventions(token,
			&lex->error_msg))
		lex->meta_count++;
	else
		lex->meta_count = 0;
	node = ft_lstnew(token);
	if (!node)
	{
		*exit = message_system_call_error("lexer");
		free(token);
		return (NULL);
	}
	lex->token_count++;
	return (node);
}

t_list	*lexer(const char *command_line, t_status *exit)
{
	t_lexer	lex;

	lexer_initialize(&lex);
	if (ft_strbapi(command_line, (bool (*)(int)) &ft_iswhitespace) == true
		|| check_lexical_conventions(command_line, exit) == false)
		return (NULL);
	if (are_quotes_closed(command_line) == false)
		return (*exit = message_general_error(E_QUOTES, command_line), NULL);
	while (*command_line && lex.meta_count < 2)
	{
		ft_skip_whitespaces(&command_line);
		if (*command_line)
		{
			lex.node = create_token_node(&command_line, exit, &lex);
			if (!lex.node)
				return (ft_lstclear(&lex.tokens, free), NULL);
			ft_lstadd_back(&lex.tokens, lex.node);
		}
	}
	if (lex.meta_count > 1 || !check_meta_conventions(ft_lstlast(
				lex.tokens)->content, &lex.error_msg))
	{
		*exit = message_general_error(E_UNEXPECTED_TOKEN, lex.error_msg);
		return (ft_lstclear(&lex.tokens, free), NULL);
	}
	return (lex.tokens);
}
