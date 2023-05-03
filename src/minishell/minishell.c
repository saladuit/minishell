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
	if (signal_ctrl_d((char *)sheldon->command_line, dict_to_envp(&sheldon->env)) == true)
		return (false);
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
	executor(sheldon);
	if (LOG)
		debug_ast(sheldon->ast);
	return (minishell_clean(sheldon));
}

static void dup_std_fds(int32_t *std_fds)
{
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	assert(std_fds[STDIN_FILENO] != ERROR && std_fds[STDOUT_FILENO] != ERROR);
}

void minishell_init(t_minishell *sheldon, char **envp)
{
	ft_bzero(sheldon, sizeof(t_minishell));
	sheldon->status = envp_load(&sheldon->env, envp);
	if (LOG)
		dict_print(&sheldon->env);
	if (!isatty(STDIN_FILENO))
	{
		sheldon->status = message_system_call_error("isatty");
		rl_outstream = stdin;
	}
	dup_std_fds(sheldon->std_fds);
	sheldon->stop = false;
}

int32_t	minishell(char **envp)
{
	t_minishell	sheldon;

	minishell_init(&sheldon, envp);
	while (minishell_loop(&sheldon) && !sheldon.stop)
		;
	dict_destroy(&sheldon.env);
	clear_history();
	return (sheldon.status);
}
