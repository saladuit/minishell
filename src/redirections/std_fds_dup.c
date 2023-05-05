#include <minishell.h>

void std_fds_dup(int32_t *std_fds)
{
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
}
