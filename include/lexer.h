#ifndef LEXER_H
# define LEXER_H

# include <libft.h>
# include <stdint.h>

typedef enum e_token
{
	PIPE,
	NEWLINE,
	GREATER,
	LESS,
	GREATGREAT,
	GREATAMP,
	ENV,
}	t_token;

int32_t	lexer(const char *command_line);

#endif
