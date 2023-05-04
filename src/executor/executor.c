/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   executor.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:36:11 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:36:11 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int32_t	setup_and_get_args(t_command *cmd, t_minishell *shell,
		char ***arguments)
{
	int32_t	status;

	status = setup_redirects(cmd);
	if (status)
	{
		shell->status = status;
		return (ERROR);
	}
	*arguments = get_arguments(cmd);
	if (!*arguments)
	{
		shell->status = E_GENERAL;
		return (ERROR);
	}
	return (SUCCESS);
}

static int32_t	execute_non_builtin(char **arguments, t_minishell *shell)
{
	pid_t	pid;
	int32_t	status;

	pid = fork();
	if (pid == ERROR)
	{
		ft_matrixfree(&arguments);
		shell->status = message_system_call_error("fork");
		return (ERROR);
	}
	if (pid == 0)
	{
		execute_child_command(shell, arguments);
		_exit(E_COMMAND_NOT_FOUND);
	}
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
	return (SUCCESS);
}

static void	execute_simple_command(t_command *cmd, t_minishell *shell)
{
	char	**arguments;

	if (setup_and_get_args(cmd, shell, &arguments) == ERROR)
		return ;
	if (*arguments == NULL)
		return ;
	if (execute_builtin(arguments, shell) == SUCCESS)
		return ;
	execute_non_builtin(arguments, shell);
}

void	executor(t_minishell *shell)
{
	t_command_table	*ct;
	t_command		*cmd;

	get_one_command_table(&shell->ast, &ct);
	if (ct->n_commands == 1)
	{
		get_next_command(ct, &cmd);
		execute_simple_command(cmd, shell);
	}
	else
		execute_pipeline(ct, shell);
	std_fds_reset(shell->std_fds, &shell->status);
}
