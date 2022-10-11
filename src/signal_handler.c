#include <minishell.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>

void	sighandler(int32_t signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int32_t	init_handlers(void)
{
	// printf("init handlers\n");
	signal(SIGINT, sighandler);
	return (SUCCESS);
}
