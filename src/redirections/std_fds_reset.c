#include <minishell.h>

void std_fds_reset(int32_t *std_fds, t_status *status)
{
  if (dup2(std_fds[STDIN_FILENO], STDIN_FILENO) == ERROR) 
    *status = message_system_call_error("std_fds_reset: ");
  if (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
    *status = message_system_call_error("std_fds_reset: ");
}

