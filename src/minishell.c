#include "message.h"
#include <minishell.h>
#include <lexer.h>
#include <parser.h>
#include <expander.h>
#include <executor.h>
#include <stdlib.h>
#include <astapi.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(t_minishell *sheldon)
{
	char		*command_line;

	//init_handlers();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line)
		ft_minishell_exit(EMALLOC);
	if (!*command_line)
		return (SUCCESS);
	lexer(command_line, &sheldon->tokens);
	if (!sheldon->tokens)
		return (SUCCESS);
	expander(sheldon);
	sheldon->ast = parser(sheldon->tokens);
	sheldon->exit_code = executor(sheldon);
	ft_lstclear(&sheldon->tokens, free);
	add_history(command_line);
	free(command_line);
	return (EXIT_SUCCESS);
}
