/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:20:44 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 13:58:09 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <message.h>
#include <stdio.h> // Remove
// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, I/O redirectors, and semicolons.

t_token	*make_token(const char *input_line, int len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->symbol = malloc(len + 1);
	ft_strlcpy(token->symbol, input_line, len);
	return (token);
}

int32_t	get_token_len(const char *input)
{
	int32_t	i;

	i = 0;
	while (!ft_iswhitespace(input[i]))
	{
		i++;
	}
	return (i);
}

int32_t	lexer(const char *input_line, t_list **tokens)
{
	int32_t	i;
	int32_t	token_len;
	t_list	*node;

	i = 0;
	(void)tokens;
	printf("%s\n", input_line);
	while (input_line[i])
	{
		if (!ft_iswhitespace(input_line[i]))
		{
			token_len = get_token_len(&input_line[i]);
			node = ft_lstnew(make_token(&input_line[i], token_len));
			ft_lstadd_back(tokens, node);
		}
		i++;
	}
	return (SUCCESS);
}
