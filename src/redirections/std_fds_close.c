#include <minishell.h>

void std_fds_close(int32_t *std_fds)
{
	close(std_fds[STDIN_FILENO]);
	close(std_fds[STDOUT_FILENO]);
}
