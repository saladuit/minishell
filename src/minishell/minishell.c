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

int32_t	minishell_loop(t_minishell *sheldon)
{
	sheldon->command_line = readline(PROMPT);
	if (!sheldon->command_line && printf("\x1B[1A" PROMPT "exit\n"))
		return (STOP);
	if (!*sheldon->command_line)
	{
		free(sheldon->command_line);
		return (CONTINUE);
	}
	add_history(sheldon->command_line);
	sheldon->tokens = lexer(sheldon->command_line, &sheldon->exit_status);
	if (!sheldon->tokens)
		return (minishell_clean(sheldon));
	sheldon->ast = parser(sheldon->tokens);
	if (!sheldon->ast)
		return (minishell_clean(sheldon));
	sheldon->exit_status = executor(sheldon);
	return (minishell_clean(sheldon));
}

int32_t	minishell(char **envp)
{
	t_minishell	sheldon;

	ft_bzero(&sheldon, sizeof(t_minishell));
	sheldon.exit_status = envp_load(&sheldon.envd, envp);
	if (DEBUG)
		dict_print(&sheldon.envd);
	if (!isatty(STDIN_FILENO))
	{
		sheldon.exit_status = handle_system_call_error("isatty");
		rl_outstream = stdin;
	}
	while (minishell_loop(&sheldon))
		;
	dict_destroy(&sheldon.envd);
	rl_clear_history();
	return (sheldon.exit_status);
}
