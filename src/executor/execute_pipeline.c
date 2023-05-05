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
	arguments = get_arguments(cmd); //TODO test wether exit status is correct
	if (!arguments)
		_exit(E_COMMAND_NOT_FOUND);
	status = execute_builtin(arguments, shell);
	if (status >= 0)
		_exit(status);
	execute_child_command(shell, arguments);
	_exit(E_COMMAND_NOT_FOUND);
	return (status);
}

static int32_t	process_command(t_command_table *ct, t_minishell *shell)
{
	t_command	*cmd;
	pid_t		pid;

	get_next_command(ct, &cmd);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
		execute_pipe_command(cmd, shell);
	return (pid);
}

void	execute_pipeline(t_command_table *ct, t_minishell *shell)
{
	int32_t	pipe_fds[2];
	int32_t	i;

	i = 0;
	shell->is_pipeline = true;
	while (i < ct->n_commands)
	{
		if (pipes_handle(pipe_fds, shell->std_fds, ct->n_commands, i) == ERROR)
		{
			shell->status = message_general_error(E_GENERAL,
					"Execute pipline: ");
			break ;
		}
		ct->pids[i] = process_command(ct, shell);
		if (ct->pids[i] == ERROR)
		{
			shell->status = message_general_error(E_GENERAL,
					"Execute pipeline: ");
			break ;
		}
		i++;
	}
	wait_for_child_processes(ct->pids, ct->n_commands, shell);
}
