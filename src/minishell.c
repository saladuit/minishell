#include <minishell.h>
#include <expander.h>
#include <executor.h>
# include <ast.h>
# include <lexer.h>
# include <parser.h>
# include <message.h>
# include <stdlib.h>
# include <astapi.h>
# include <minisignal.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(t_minishell *sheldon)
{
	char		*command_line;

	setup_signals();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line)
	{
		ft_printf("EXIT\n");
		return (EXIT_SUCCESS);
	}
	if (!*command_line)
	{
		ft_printf("empty\n");
		return (SUCCESS);
	}
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
