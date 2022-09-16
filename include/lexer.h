/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:02:56 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 11:33:35 by dritsema      ########   odam.nl         */
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
