#include <minishell.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(char **envp)
{
	t_list		*abstract_syntax_tree;
	t_list		*tokens;
	const char	*command_line; // should be converted into dlist

	abstract_syntax_tree = NULL;
	command_line = NULL;
	while (true)
	{
		command_line = readline(messages_lookup(PROMPT));
		if (lexer(command_line, &tokens) == ERROR)
			return (EXIT_FAILURE);
		if (parser(&abstract_syntax_tree, tokens) == ERROR)
			return (EXIT_FAILURE);
//		if (expander(command_table) == ERROR)
//			return (EXIT_FAILURE);
		if (executor(abstract_syntax_tree, envp) == ERROR)
			return (EXIT_FAILURE);
		// return (EXIT_SUCCESS);
	}
}
