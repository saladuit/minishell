#include <minishell.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(t_minishell *sheldon)
{
	char		*command_line;

	setup_signals();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line && ft_printf("exit"))
		exit(E_GENERAL);
	if (!*command_line)
		return (SUCCESS);
	lexer(command_line, &sheldon->tokens);
	if (analyzer(sheldon->tokens))
		return (EXIT_FAILURE);
	if (!sheldon->tokens)
		return (SUCCESS);
	sheldon->ast = parser(sheldon->tokens);
	expander(sheldon);
	sheldon->exit_code = executor(sheldon);
	ft_lstclear(&sheldon->tokens, free);
	add_history(command_line);
	free(command_line);
	return (EXIT_SUCCESS);
}
