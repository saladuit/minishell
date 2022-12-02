#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

void	sigint_hook(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_hook);
}
