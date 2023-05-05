/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   pipe.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 15:51:44 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 15:51:44 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int32_t	pipe_handle_first_command(int32_t *pipe_fds)
{
	if (pipe(pipe_fds) == ERROR)
		return (ERROR);
	if (dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
		return (ERROR);
	return (close(pipe_fds[STDOUT_FILENO]));
}

static int32_t	pipe_handle_middle_command(int32_t *pipe_fds)
{
	if (dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
		return (ERROR);
	if (close(pipe_fds[STDIN_FILENO]) == ERROR)
		return (ERROR);
	if (pipe(pipe_fds) == ERROR)
		return (ERROR);
	if (dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
		return (ERROR);
	return (close(pipe_fds[STDOUT_FILENO]));
}

static int32_t	pipe_handle_last_command(int32_t *pipe_fds, int32_t *std_fds)
{
	if (dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
		return (ERROR);
	if (close(pipe_fds[STDIN_FILENO]) == ERROR)
		return (ERROR);
	return (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO));
}

int32_t	pipes_handle(int32_t *pipe_fds, int32_t *std_fds, int32_t n_commands,
		int32_t i)
{
	if (i == 0)
		return (pipe_handle_first_command(pipe_fds));
	else if (i == n_commands - 1)
		return (pipe_handle_last_command(pipe_fds, std_fds));
	return (pipe_handle_middle_command(pipe_fds));
}
