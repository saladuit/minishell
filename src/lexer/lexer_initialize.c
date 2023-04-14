#include <minishell.h>

void	lexer_initialize(t_lexer *lex)
{
	ft_bzero(lex, sizeof(t_lexer));
	lex->token_count = 0;
	lex->meta_count = 0;
	lex->error_msg = NULL;
	lex->tokens = NULL;
}
