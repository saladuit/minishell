#include <minishell.h>

void	lexer_initialize(t_lexer *lex)
{
	lex->token_count = 0;
	lex->meta_count = 0;
	lex->error_msg = NULL;
	lex->tokens = NULL;
}