/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   lexer_check.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/12 11:50:24 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/12 11:50:24 by safoh        \___)=(___/                 */
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

bool	check_final_conditions(t_lexer *lex, t_status *exit)
{
	if (lex->meta_count > 1 || !check_meta_conventions(ft_lstlast(
				lex->tokens)->content, &lex->error_msg))
	{
		*exit = message_general_error(E_UNEXPECTED_TOKEN, lex->error_msg);
		ft_lstclear(&lex->tokens, free);
		return (false);
	}
	return (true);
}

bool	check_initial_conditions(const char *command_line, t_status *exit)
{
	if (ft_strbapi(command_line, is_whitespace) == true
		|| check_lexical_conventions(command_line, exit) == false
		|| are_quotes_closed(command_line) == false)
	{
		if (!are_quotes_closed(command_line))
			*exit = message_general_error(E_QUOTES, command_line);
		return (false);
	}
	return (true);
}
