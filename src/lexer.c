/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:20:44 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 09:26:21 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <message.h>
#include <stdio.h> // Remove

int32_t	lexer(char *input_line, char **envp, t_list **tokens)
{
	(void)envp;
	(void)tokens;
	printf("%s\n", input_line);

	free(input_line);
	return (SUCCESS);
}
