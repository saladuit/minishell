/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:02:56 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 17:21:26 by safoh        \___)=(___/                 */
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

typedef enum e_token
{
	PIPE,
	NEWLINE,
	GREATER,
	LESS,
	GREATGREAT,
	LESS,
	GREATAMP,
	ENV,
}	t_token;

int32_t	lexer(const char *command_line, t_list **tokens);

#endif
