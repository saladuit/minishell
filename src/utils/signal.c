#include <minishell.h>
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// 30 is an arbitrary number that most likely is not used as a legit exit code.
// Thus it only ever happens when interupting heredoc.
void	execution_sigint_handler(int sig)
{
	(void)sig;
	// g_exitcode = E_CTRL_C;
}

void	execution_sigquit_handler(int sig)
{
	(void)sig;
	// g_exitcode = S_EXEC_QUIT;
	// printf("Quit: %i\n", g_exitcode);
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// g_exitcode = S_HEREDOC;
}

// void	executor_signal_setup(void)
// {
// 	signal(SIGINT, execution_signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	setup_signals(t_signal_handler handler)
{
	if (handler == SREADLINE)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (handler == SHEREDOC)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (handler == SEXECUTOR)
	{
		signal(SIGINT, execution_sigint_handler);
		signal(SIGQUIT, execution_sigquit_handler);
	}
}
//	struct termios tio;
//	tcgetattr(STDIN_FILENO, &tio);
//	tcsetattr(STDIN_FILENO, TCSANOW, &tio);
// return (SUCCESS);

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_noncanonical_termios_mode(void)
{
	struct termios	oldtio;
	struct termios	newtio;

	tcgetattr(STDIN_FILENO, &oldtio);
	newtio.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	newtio.c_oflag &= ~OPOST;
	newtio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	newtio.c_cflag &= ~(CSIZE | PARENB);
	newtio.c_cflag |= CS8;
	tcsetattr(STDIN_FILENO, TCSANOW, &newtio);
}
//void setup_interactive_mode_signals(void)
//{
//	struct sigaction sa;
//
//	sa.sa_flags = ;
//	sa.sa_mask = ;
//	sigaction(SIGINT, sa, NULL);
//}
