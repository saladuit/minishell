/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:20:44 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 09:43:03 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <message.h>
#include <stdio.h> // Remove

t_token	*get_next_token()
{

}

int32_t	lexer(char *input_line, char **envp, t_list **tokens)
{
	int	i;

	(void)envp;
	(void)tokens;
	printf("%s\n", input_line);
	while (input_line[i])
	{
		if (!ft_iswhitespace(input_line[i]))

		i++;
	}
	free(input_line);
	return (SUCCESS);
}
