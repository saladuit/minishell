#include <minishell.h>

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(t_minishell *sheldon)
{
	char	*command_line;

	//setup_signals(SREADLINE);
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line && printf("\x1B[1AMinishell$ exit\n"))
		return (STOP);
	if (!*command_line)
		return (CONTINUE);
	add_history(command_line);
	lexer(command_line, &sheldon->tokens);
	if (!sheldon->tokens)
		return (CONTINUE);
	sheldon->ast = parser(sheldon->tokens);
#ifdef DEBUG
	debug_ast(sheldon->ast);
#endif
	//	if (g_exitcode == 300)
	//	{
	//		g_exitcode = 0;
	//		return (SUCCESS);
	//	}
	//	expander(sheldon);
	//	g_exitcode = 0;
	//	g_exitcode = executor(sheldon);
	ft_lstclear(&sheldon->tokens, free);
	deconstruct_ast(&sheldon->ast);
	free(command_line);
	return (CONTINUE);
}
