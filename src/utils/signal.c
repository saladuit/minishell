#include <minishell.h>

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

//void setup_interactive_mode_signals(void)
//{
//	struct sigaction sa;
//
//	sa.sa_flags = ;
//	sa.sa_mask = ;
//	sigaction(SIGINT, sa, NULL);
//}
