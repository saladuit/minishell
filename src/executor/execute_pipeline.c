/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   execute_pipeline.c                              |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 17:51:37 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 17:51:37 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	wait_for_child_processes(pid_t *pid_array, size_t array_length,
		t_minishell *shell)
{
	int32_t	status;
	size_t	i;

	i = 0;
	while (i < array_length)
	{
		waitpid(pid_array[i], &status, WUNTRACED);
		if (WIFEXITED(status))
			shell->status = WEXITSTATUS(status);
		i++;
	}
	while (waitpid(-1, &status, WUNTRACED) > 0)
		;
}

static int32_t	execute_pipe_command(t_command *cmd, t_minishell *shell)
{
	char	**arguments;
	int32_t	status;

	status = setup_redirects(cmd);
	if (status)
		_exit(E_COMMAND_NOT_FOUND);
	arguments = get_arguments(cmd);
	if (!arguments)
		_exit(E_COMMAND_NOT_FOUND);
	status = execute_builtin(arguments, shell);
	if (status >= 0)
		_exit(status);
	execute_child_command(shell, arguments);
	_exit(E_COMMAND_NOT_FOUND);
	return (status);
}

static void	process_command(t_execute *command, int32_t *i,
							t_command_table *ct, t_minishell *shell)
{
	t_command	*cmd;

	if (pipe(command->pipe_fds) == ERROR)
		return ;
	get_next_command(ct, &cmd);
	command->pid = fork();
	if (command->pid == ERROR)
		return ;
	if (command->pid == 0)
	{
		if (pipes_handle(command->pipe_fds, ct->n_commands, *i,
				command->prev_read) == ERROR)
		{
			close_pipe(command->pipe_fds);
			_exit(message_general_error(E_GENERAL, "Execute pipeline: "));
		}
		execute_pipe_command(cmd, shell);
	}
}

void	execute_pipeline(t_command_table *ct, t_minishell *shell)
{
	t_execute	command;
	int32_t		i;

	i = 0;
	shell->is_pipeline = true;
	while (i < ct->n_commands)
	{
		process_command(&command, &i, ct, shell);
		if (i)
			close(command.prev_read);
		command.prev_read = command.pipe_fds[READ_END];
		close(command.pipe_fds[WRITE_END]);
		ct->pids[i] = command.pid;
		if (ct->pids[i] == ERROR)
		{
			close_pipe(command.pipe_fds);
			shell->status = message_general_error(E_GENERAL,
					"Execute pipeline: ");
			break ;
		}
		i++;
	}
	close(command.pipe_fds[READ_END]);
	wait_for_child_processes(ct->pids, ct->n_commands, shell);
}
