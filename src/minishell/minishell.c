/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safoh <safoh@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:40:08 by safoh             #+#    #+#             */
/*   Updated: 2023/05/04 11:40:09 by safoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	signal_error = E_USAGE;

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
	if (signal_error)
		sheldon->status = E_GENERAL;
	if (signal_ctrl_d((char *)sheldon->command_line, dict_to_envp(&sheldon->env), &sheldon->status) == true)
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
	if (LOG)
		debug_ast(sheldon->ast);
	executor(sheldon);
	return (minishell_clean(sheldon));
}

void	minishell_init(t_minishell *sheldon, char **envp)
{
	ft_bzero(sheldon, sizeof(t_minishell));
	initialize_signal_handling(&sheldon->status);
	sheldon->status = envp_load(&sheldon->env, envp);
	if (LOG)
		dict_print(&sheldon->env);
	if (!isatty(STDIN_FILENO))
	{
		sheldon->status = message_system_call_error("isatty");
		rl_outstream = stdin;
	}
	std_fds_dup(sheldon->std_fds);
	sheldon->stop = false;
}

void	minishell_deinit(t_minishell *sheldon)
{
	dict_destroy(&sheldon->env);
	std_fds_close(sheldon->std_fds);
	clear_history();
	rl_cleanup_after_signal();
	rl_free_line_state();
	rl_free_undo_list();
	rl_deprep_terminal();
}

int32_t	minishell(char **envp)
{
	t_minishell	sheldon;

	minishell_init(&sheldon, envp);
	while (minishell_loop(&sheldon) && !sheldon.stop)
		;
	minishell_deinit(&sheldon);
	return (sheldon.status);
}
