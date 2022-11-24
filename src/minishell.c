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
	t_minishell	sheldon;
	char		*command_line;

	(void)envp;
	sheldon.env = dup_envp(envp);
	if (sheldon.env == NULL)
		return (ft_minishell_exit(EMALLOC));
	//init_handlers();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line)
		ft_minishell_exit(EMALLOC);
	if (!*command_line)
		return (SUCCESS);
	lexer(command_line, &sheldon.tokens);
	expander(&sheldon);
	sheldon.ast = parser(sheldon.tokens);
	executor(sheldon.ast, sheldon.env);
	ft_lstclear(&sheldon.tokens, free);
	free(command_line);
	return (EXIT_SUCCESS);
}
