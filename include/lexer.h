/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:02:56 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 14:30:51 by safoh        \___)=(___/                 */
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

int32_t	lexer(const char *input_line, t_list **tokens);

#endif
