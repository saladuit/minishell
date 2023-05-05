/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_initialize.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:29:06 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:29:07 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lexer_initialize(t_lexer *lex)
{
	ft_bzero(lex, sizeof(t_lexer));
	lex->token_count = 0;
	lex->meta_count = 0;
	lex->error_msg = NULL;
	lex->tokens = NULL;
}
