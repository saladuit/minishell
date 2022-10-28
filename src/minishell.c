#include "ast.h"
#include <minishell.h>
#include <lexer.h>
#include <parser.h>
#include <expander.h>
#include <executor.h>
#include <stdlib.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */
int32_t	clean_minishell(char **cl, t_list **tokens, t_list **ast)
{
	if (*cl)
	{
		free(*cl);
		*cl = NULL;
	}
	if (*tokens)
	{
		ft_lstclear(tokens, free);
		*tokens = NULL;
	}
	if (*ast)
	{
		ft_lstclear(ast, free);
		*ast = NULL;
	}
	return (EXIT_FAILURE);
}

int32_t	minishell(char **envp)
{
	t_list		*ast;
	t_list		*tokens;
	char		*command_line; // should be converted into dlist

	init_handlers();
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line)
		return (EXIT_FAILURE);
	if (lexer(command_line, &tokens) == ERROR)
		return (clean_minishell(&command_line, NULL, NULL));
	if (parser(&ast, tokens) == ERROR)
		return (clean_minishell(&command_line, &tokens, &ast));
	//		if (expander(command_table) == ERROR)
	//			return (EXIT_FAILURE);
	if (executor(ast, envp) == ERROR) // Fix segfault
		return (clean_minishell(&command_line, &tokens, &ast));
	ft_lstclear(&tokens, free);
	deconstruct_ast(&ast);
	free(command_line);
	return (EXIT_SUCCESS);
}
