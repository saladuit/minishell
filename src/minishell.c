#include <minishell.h>

int				g_exitcode;

static int32_t	minishell_clean(t_minishell *sheldon)
{
	if (sheldon->tokens)
		ft_lstclear(&sheldon->tokens, free);
	if (sheldon->ast)
		deconstruct_ast(&sheldon->ast);
	if (sheldon->command_line)
		free(sheldon->command_line);
	return (CONTINUE);
}

int32_t	minishell(t_minishell *sheldon)
{
	// setup_signals(SREADLINE);
	sheldon->command_line = readline(PROMPT);
//	sheldon->command_line = ft_strdup("cat Makefile < cat.out");
	if (!sheldon->command_line && printf("\x1B[1A"PROMPT"exit\n"))
		return (STOP);
	if (!*sheldon->command_line)
	{
		free(sheldon->command_line);
		return (CONTINUE);
	}
	add_history(sheldon->command_line);
	if (lexer(sheldon->command_line, &sheldon->tokens) == ERROR)
		return (minishell_clean(sheldon));
	sheldon->ast = parser(sheldon->tokens);
	if (!sheldon->ast)
		return (minishell_clean(sheldon));
	//	expander(sheldon);
	g_exitcode = executor(sheldon);
	return (minishell_clean(sheldon));
}
