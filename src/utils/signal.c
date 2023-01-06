#include <minishell.h>
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


int32_t	setup_signals(void)
{
//	struct termios tio;

//	tcgetattr(STDIN_FILENO, &tio);
//	tcsetattr(STDIN_FILENO, TCSANOW, &tio);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_noncanonical_termios_mode(void)
{
	struct termios oldtio;
	struct termios newtio;

	tcgetattr(STDIN_FILENO, &oldtio);
	newtio.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
	newtio.c_oflag &= ~OPOST;
	newtio.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
	newtio.c_cflag &= ~(CSIZE|PARENB);
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
