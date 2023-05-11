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

void	close_pipe(int32_t *pipe_fd)
{
	if (close(pipe_fd[READ_END]) != SUCCESS)
		_exit(E_COMMAND_NOT_FOUND);
	if (close(pipe_fd[WRITE_END]) != SUCCESS)
		_exit(E_COMMAND_NOT_FOUND);
}

static int32_t	pipe_handle_first_command(int32_t *pipe_fds)
{
	close(pipe_fds[READ_END]);
	if (dup2(pipe_fds[WRITE_END], STDOUT_FILENO) == ERROR)
		return (ERROR);
	return (close(pipe_fds[WRITE_END]));
}

static int32_t	pipe_handle_middle_command(int32_t *pipe_fds, int32_t prev_read)
{
	if (dup2(prev_read, STDIN_FILENO) == ERROR)
		return (ERROR);
	if (close(pipe_fds[READ_END]) == ERROR)
		return (ERROR);
	if (dup2(pipe_fds[WRITE_END], STDOUT_FILENO) == ERROR)
		return (ERROR);
	return (close(pipe_fds[WRITE_END]));

}

static int32_t	pipe_handle_last_command(int32_t *pipe_fds, int32_t prev_read)
{
	close(pipe_fds[WRITE_END]);
	if (dup2(prev_read, STDIN_FILENO) == ERROR)
		return (ERROR);
	return (close(pipe_fds[READ_END]));
}

int32_t	pipes_handle(int32_t *pipe_fds, int32_t n_commands,
		int32_t i, int32_t prev_read)
{
	if (i == 0)
		return (pipe_handle_first_command(pipe_fds));
	else if (i == n_commands - 1)
		return (pipe_handle_last_command(pipe_fds, prev_read));
	return (pipe_handle_middle_command(pipe_fds, prev_read));
}
