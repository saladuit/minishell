#include <minishell.h>

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
	if (!sheldon->command_line)
		return (STOP);
	if (!*sheldon->command_line)
	{
		free(sheldon->command_line);
		return (CONTINUE);
	}
	add_history(sheldon->command_line);
	sheldon->tokens = lexer(sheldon->command_line, &sheldon->status);
	if (!sheldon->tokens)
		return (minishell_clean(sheldon));
	sheldon->ast = parser(sheldon->tokens, &sheldon->status, &sheldon->env);
	if (!sheldon->ast)
		return (minishell_clean(sheldon));
	sheldon->status = executor(sheldon);
	return (minishell_clean(sheldon));
}

int32_t	minishell(char **envp)
{
	t_minishell	sheldon;

	ft_bzero(&sheldon, sizeof(t_minishell));
	sheldon.status = envp_load(&sheldon.env, envp);
	if (DEBUG)
		dict_print(&sheldon.env);
	if (!isatty(STDIN_FILENO))
	{
		sheldon.status = message_system_call_error("isatty");
		rl_outstream = stdin;
	}
	while (minishell_loop(&sheldon))
		;
	dict_destroy(&sheldon.env);
	rl_clear_history();
	return (sheldon.status);
}
