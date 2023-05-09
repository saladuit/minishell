/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 09:57:13 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/09 09:57:15 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_signal_error = E_GENERAL;
	rl_on_new_line();
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
}

bool	signal_ctrl_d(char *str, char **env, t_status *status)
{
	(void)env;
	(void)status;
	if (str)
		return (false);
	return (true);
}

void	initialize_signal_handling(t_status *status)
{
	(void)status;
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signal_ctrl_c_heredoc(int sig)
{
	(void)sig;
	_exit(E_COMMAND_NOT_FOUND);
}

void	initialize_signal_handling_for_execve(t_status *status)
{
	(void)status;
	signal(SIGQUIT, signal_ctrl_c_heredoc);
}
