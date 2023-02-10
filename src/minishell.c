#include <minishell.h>

int	 g_exitcode;

static void minishell_clean(t_minishell *sheldon)
{
	ft_lstclear(&sheldon->tokens, free);
	deconstruct_ast(&sheldon->ast);
	free(sheldon->command_line);
}

int32_t	minishell(t_minishell *sheldon)
{
	//setup_signals(SREADLINE);
	sheldon->command_line = readline(messages_lookup(PROMPT));
	if (!sheldon->command_line && printf("\x1B[1AMinishell$ exit\n"))
		return (STOP);
	if (!*sheldon->command_line)
		return (CONTINUE);
	add_history(sheldon->command_line);
	lexer(sheldon->command_line, &sheldon->tokens);
	if (!sheldon->tokens)
		return (CONTINUE);
	sheldon->ast = parser(sheldon->tokens);
	if (DEBUG)
		debug_ast(sheldon->ast);
	//	if (g_exitcode == 300)
	//	{
	//		g_exitcode = 0;
	//		return (SUCCESS);
	//	}
	//	expander(sheldon);
	//	g_exitcode = 0;
	//	g_exitcode = executor(sheldon);
	minishell_clean(sheldon);
	return (CONTINUE);
}
