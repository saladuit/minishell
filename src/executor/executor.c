#include <minishell.h>

int32_t	redirect(t_redir *redir, t_type type)
{
	if (!open_redir(redir->filename, type))
		return (message_system_call_error("redirect"));
	return (SUCCESS);
}

int32_t	setup_redirects(t_command *command)
{
	t_redir	*redir;
	int32_t	ret;
	int32_t	i;

	i = 0;
	ret = 0;
	while (i++ < command->n_redirs)
	{
		get_next_redir(command, &redir);
		ret = redirect(redir, redir->type);
	}
	return (ret);
}

t_builtin	builtin_lookup(char *cmd)
{
	int32_t	i;

	static const t_builtin lookup[] = {
		{.name = "echo", .func = ft_echo},
		{.name = "cd", .func = ft_cd},
		{.name = "pwd", .func = ft_pwd},
		{.name = "export", .func = ft_export},
		{.name = "unset", .func = ft_unset},
		{.name = "env", .func = ft_env},
		{.name = "exit", .func = ft_exit},
		{NULL, NULL}};
	i = 0;
	while (lookup[i].name != NULL &&
			ft_strncmp(lookup[i].name, cmd, ft_strlen(cmd) + 1))
		i++;
	return (lookup[i]);
}

int32_t	execute_builtin(char **arguments, t_minishell *shell)
{
	t_builtin	builtin_function;
	int32_t		ret;

	builtin_function = builtin_lookup(arguments[0]);
	if (builtin_function.name == NULL)
		return (-1);
	ret = builtin_function.func(arguments, shell);
	return (ret);
}

int32_t	wait_for_child_processes(pid_t pid)
{
	int32_t	status;

	status = 0;
	close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) != -1 && errno != ECHILD)
		;
	// if (g_exitcode == E_CTRL_C)
	// 	return (E_CTRL_C);
	// if (g_exitcode == S_EXEC_QUIT)
	// {
	// 	printf("Quit: 3\n");
	// 	return (WEXITSTATUS(status));
	// }
	return (WEXITSTATUS(status));
}

void	execute_child_command(t_minishell *shell, char **arguments)
{
	char	*command_path;

	command_path = get_cmd_path(&shell->env, arguments[0]);
	if (!command_path)
	{
		message_system_call_error("malloc");
		_exit(E_COMMAND_NOT_FOUND);
	}
	if (access(command_path, X_OK))
	{
		free(command_path);
		message_system_call_error("access");
		_exit(E_COMMAND_NOT_FOUND);
	}
	execve(command_path, arguments, dict_to_envp(&shell->env));
	message_system_call_error("execve");
	_exit(E_COMMAND_NOT_FOUND);
}

// Needs to always exit even if it is builtin
int32_t	execute_pipe_command(t_command *cmd, t_minishell *shell)
{
	char	**arguments;
	int32_t	status;

	status = setup_redirects(cmd);
	if (status)
		_exit(status);
	arguments = get_arguments(cmd);
	if (!arguments)
		_exit(E_COMMAND_NOT_FOUND);
	status = execute_builtin(arguments, shell);
	if (status >= 0)
		_exit(E_COMMAND_NOT_FOUND);
	execute_child_command(shell, arguments);
	_exit(E_COMMAND_NOT_FOUND);
	return (status);
}

int32_t	execute_simple_command(t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	int32_t	status;
	char	**arguments;

	status = setup_redirects(cmd);
	if (status)
		return (status);
	arguments = get_arguments(cmd);
	if (!arguments)
	{
		free(arguments);
		return (1);
	}
	status = execute_builtin(arguments, shell);
	if (status >= 0)
	{
		free(arguments);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		execute_child_command(shell, arguments);
		_exit(127);
	}
	free(arguments);
	return (wait_for_child_processes(pid));
}

int32_t create_pipe(int32_t *pipe_fds)
{
    if (pipe(pipe_fds) == -1)
        return (ERROR);
    return (SUCCESS);
}

int32_t duplicate_fd(int32_t old_fd, int32_t new_fd)
{
    if (dup2(old_fd, new_fd) == -1)
        return (ERROR);
    return (SUCCESS);
}

int32_t close_fd(int32_t fd)
{
    if (close(fd) == -1)
        return (ERROR);
    return (SUCCESS);
}

int32_t handle_first_pipe(int32_t *pipe_fds)
{
    if (create_pipe(pipe_fds) == ERROR)
        return (ERROR);
    if (duplicate_fd(pipe_fds[1], STDOUT_FILENO) == ERROR)
        return (ERROR);
    return close_fd(pipe_fds[1]);
}

int32_t handle_middle_pipes(int32_t *pipe_fds)
{
    if (duplicate_fd(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
        return (ERROR);
    if (close_fd(pipe_fds[STDIN_FILENO]) == ERROR)
        return (ERROR);
    if (create_pipe(pipe_fds) == ERROR)
        return (ERROR);
    if (duplicate_fd(pipe_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
        return (ERROR);
    return close_fd(pipe_fds[STDOUT_FILENO]);
}

int32_t handle_last_pipe(int32_t *pipe_fds, int32_t *std_fds)
{
    if (duplicate_fd(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
        return (ERROR);
    if (close_fd(pipe_fds[STDIN_FILENO]) == ERROR)
        return (ERROR);
    return duplicate_fd(std_fds[STDOUT_FILENO], STDOUT_FILENO);
}

int32_t process_command(int32_t *pipe_fds, t_command_table *ct, t_minishell *shell)
{
    t_command *cmd;
    pid_t pid;

    get_next_command(ct, &cmd);
    pid = fork();
    if (pid == -1)
				return (E
    if (pid == 0)
    {
        close(pipe_fds[STDIN_FILENO]);
        execute_pipe_command(cmd, shell);
    }
    return (pid);
}

int32_t handle_pipes(int32_t *pipe_fds, int32_t *std_fds, int32_t n_commands, int32_t i)
{
		if (i == 0)
			return (handle_first_pipe(pipe_fds));
		else if (i == n_commands - 1)
			return (handle_last_pipe(pipe_fds, std_fds));
		return (handle_middle_pipes(pipe_fds));
}

void execute_pipeline(t_command_table *ct, t_minishell *shell)
{
  int32_t pipe_fds[2];
  int32_t pid;
  int32_t i;

  i = 0;
  shell->is_pipeline = true;
  while (i < ct->n_commands)
  {
  	if (handle_pipes(pipe_fds, shell->std_fds, ct->n_commands, i) == ERROR)
  	{
  		shell->message_general_error(s);
  		shell->status = E_GENERAL;
  		break ;
  	}
  	pid = process_command(pipe_fds, ct, shell);
    i++;
  }
  shell->status = wait_for_child_processes(pid);
}

void		execute_command_table(t_command_table *ct, t_minishell *shell)
{
	t_command	*cmd;

	if (ct->n_commands == 1)
	{
		get_next_command(ct, &cmd);
		execute_simple_command(cmd, shell);
	}
	else
		execute_pipeline(ct, shell);
}

void reset_std_fds(int32_t *std_fds)
{
	assert(dup2(std_fds[STDIN_FILENO], STDIN_FILENO) == SUCCESS);
	assert(dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == SUCCESS);
	assert(close(std_fds[STDIN_FILENO] == SUCCESS));
	assert(close(std_fds[STDOUT_FILENO] == SUCCESS));
}

void	executor(t_minishell *shell)
{
	t_command_table	*ct;

	get_one_command_table(&shell->ast, &ct);
	execute_command_table(ct, shell);
	reset_std_fds(shell->std_fds);
}
