#include <minishell.h>

void	signal_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	signal_error = E_GENERAL;
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
	signal_error = E_USAGE;
	*status = E_USAGE;
	ft_putstr_fd("exit", STDOUT_FILENO);
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
	signal(SIGINT, SIG_IGN);
}
