#include <minishell.h>

void	signal_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ctrl_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	exit(errno);
}

bool	signal_ctrl_d(char *str, char **env)
{
	(void)env;
	if (str)
		return (false);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (true);
}

void	initialize_signal_handling(void)
{
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, signal_ctrl_heredoc);
}