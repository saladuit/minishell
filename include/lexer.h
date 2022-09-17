#ifndef LEXER_H
# define LEXER_H

# include <libft.h>
# include <stdint.h>

typedef enum e_token
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
