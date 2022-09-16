/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:44:40 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 11:34:25 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdbool.h>

// input_line gets freed in lexer.
int32_t	minishell(char **envp)
{
	t_tree	*command_table;
	t_list	*tokens;
	char	*input_line;

	command_table = NULL;
	tokens = NULL;
	(void)envp;
	while (true)
	{
		input_line = readline(messages_lookup(PROMPT));
		if (lexer(input_line, &tokens) == ERROR)
			return (EXIT_FAILURE);
		free(input_line);
		if (parser(tokens, &command_table) == ERROR)
			return (EXIT_FAILURE);
		if (expander(command_table) == ERROR)
			return (EXIT_FAILURE);
		if (executor(command_table) == ERROR)
			return (EXIT_FAILURE);
		// return (EXIT_SUCCESS);
	}
}
