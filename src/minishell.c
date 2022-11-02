#include "ast.h"
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

int32_t	minishell(char **envp)
{
	t_list		*ast;
	t_list		*tokens;
	char		*command_line;

	(void)envp;
	//init_handlers();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line)
		ft_minishell_exit(EMALLOC);
	if (!*command_line)
		return (SUCCESS);
	lexer(command_line, &tokens);
	ast = parser(tokens);
	executor(ast, envp);
	ft_lstclear(&tokens, NULL);
	free(command_line);
	return (EXIT_SUCCESS);
}
