/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:02:56 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/17 14:48:33 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <libft.h>
# include <stdint.h>

typedef struct s_token
{
	int32_t	type;
	char	*symbol;
}	t_token;

typedef enum e_token_type
{
	TOK_LESS,
	TOK_GREAT,
	TOK_DGREAT,
	TOK_DLESS,
	TOK_DOLLAR,
	TOK_QUOTE,
	TOK_SPACE,
	TOK_PIPE,
	TOK_WORD,
	TOK_DQUOTE,
	TOK_MERGE,
}	t_token_type;

int32_t	lexer(const char *command_line, t_list **tokens);

#endif
