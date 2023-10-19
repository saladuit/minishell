/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minishell.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:36:02 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:36:02 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_signal_error = E_USAGE;

static int32_t minishell_clean(t_minishell *shell)
{
	if (shell->tokens)
		ft_lstclear(&shell->tokens, free);
	if (shell->ast)
		deconstruct_ast(&shell->ast);
	if (shell->command_line)
		free(shell->command_line);
	return (CONTINUE);
}

int32_t minishell_loop(t_minishell *shell)
{
	shell->command_line = readline(PROMPT);
	if (g_signal_error)
		set_status_reset_signal(&shell->status);
	if (!shell->command_line)
		return (STOP);
	if (!*shell->command_line)
	{
		free(shell->command_line);
		return (CONTINUE);
	}
	add_history(shell->command_line);
	shell->tokens = lexer(shell->command_line, &shell->status);
	if (!shell->tokens)
		return (minishell_clean(shell));
	shell->ast = parser(shell->tokens, &shell->status, &shell->env);
	if (!shell->ast)
		return (minishell_clean(shell));
	if (LOG)
		debug_ast(shell->ast);
	executor(shell);
	return (minishell_clean(shell));
}

void minishell_init(t_minishell *shell, char **envp)
{
	ft_bzero(shell, sizeof(t_minishell));
	initialize_signal_handling(&shell->status);
	shell->status = envp_load(&shell->env, envp);
	if (LOG)
		dict_print(&shell->env, STDOUT_FILENO);
	if (!isatty(STDIN_FILENO))
	{
		message_system_call_error("isatty");
		rl_outstream = stdin;
	}
}

void minishell_deinit(t_minishell *shell)
{
	dict_destroy(&shell->env);
	clear_history();
}

int32_t minishell(char **envp)
{
	t_minishell shell;

	minishell_init(&shell, envp);
	while (minishell_loop(&shell) && !shell.stop)
		;
	minishell_deinit(&shell);
	return (shell.status);
}
