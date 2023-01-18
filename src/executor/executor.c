#include <minishell.h>

int32_t	redirect(t_redir *redir, t_type type)
{
	if (!open_redir(redir->filename, type))
	{
		perror(ft_strjoin("Minishell: ", redir->filename));
		return (ERROR);
	}
	return (SUCCESS);
}

int32_t	setup_redirects(t_command *command)
{
	t_redir	*redir;
	int32_t	ret;

	ret = SUCCESS;
	redir = get_next_redir(command);
	while (redir)
	{
		if (redir->type == INPUT)
			ret = redirect(redir, INPUT);
		if (redir->type == OUTPUT)
			ret = redirect(redir, OUTPUT);
		free(redir);
		redir = get_next_redir(command);
	}
	return (ret);
}

t_builtin	builtin_lookup(char *cmd)
{
	const static t_builtin	lookup[] = {
	{.name = "echo", .func = ft_echo},
	{.name = "cd", .func = ft_cd},
	{.name = "pwd", .func = ft_pwd},
	{.name = "export", .func = ft_export},
	{.name = "unset", .func = ft_unset},
	{.name = "env", .func = ft_env},
	{.name = "exit", .func = ft_exit},
	{NULL, NULL}};
	int32_t					i;

	i = 0;
	while (lookup[i].name != NULL
		&& ft_strncmp(lookup[i].name, cmd, ft_strlen(cmd) + 1))
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
	ft_matrixfree(&arguments);
	return (ret);
}

int32_t	wait_for_child_processes(pid_t pid)
{
	int32_t	status;

	status = 0;
	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) != -1 && errno != ECHILD)
		;
	return (WEXITSTATUS(status));
}

void	execute_child_command(t_minishell *shell, char **arguments)
{
	char	*command_path;

	command_path = get_cmd_path(shell->env, arguments[0]);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found"); // TODO stderr
	execve(command_path, arguments, shell->env);
	exit(127); // TODO make one func call
}
// Needs to always exit even if it is builtin
int32_t	execute_pipe_command(t_command *cmd, t_minishell *shell)
{
	char	**arguments;
	int32_t	status;

	arguments = get_arguments(cmd);
	setup_redirects(cmd);
	if (!arguments)
		exit(0);
	status = execute_builtin(arguments, shell);
	free(cmd); // TODO Fix leaks if any.
	if (status >= 0)
		exit(status);
	reset_signals();
	execute_child_command(shell, arguments);
	return (0);
}

int32_t	execute_simple_command(t_command *cmd, t_minishell *shell)
{
	pid_t		pid;
	int32_t		status;
	char		**arguments;

	arguments = get_arguments(cmd);
	setup_redirects(cmd);
	free(cmd);
	reset_signals();
	if (!arguments)
		return (0);
	status = execute_builtin(arguments, shell);
	setup_signals();
	if (status >= 0)
		return (status);
	pid = fork();
	if (pid != 0)
		return (wait_for_child_processes(pid));
	execute_child_command(shell, arguments);
	return (0);
}

int32_t	init_first_pipe(int32_t *pipe_fds)
{
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[1]);
	return (SUCCESS);
}

int32_t	prepare_next_pipe(int32_t *pipe_fds, int32_t *std_fds, bool last)
{
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[0]);
	if (last)
	{
		if (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (pipe(pipe_fds) == -1)
			return (ERROR);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			return (ERROR);
		close(pipe_fds[1]);
	}
	return (SUCCESS);
}

int32_t	execute_pipeline(t_command_table *ct, int32_t *std_fds, t_minishell *shell)
{
	t_command	*cmd;
	int32_t		pipe_fds[2];
	pid_t		pid;

	if (init_first_pipe(pipe_fds) == -1)
		return (ERROR);
	cmd = get_next_command(ct);
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
			execute_pipe_command(cmd, shell);
		free(cmd); // Leaks content should also be freed as this is the parent
		cmd = get_next_command(ct);
		if (!cmd)
			break ;
		if (ct->commands)
			prepare_next_pipe(pipe_fds, std_fds, false);
		else
			prepare_next_pipe(pipe_fds, std_fds, true);
	}
	return (wait_for_child_processes(pid));
}

int32_t	execute_command_table(t_command_table *ct,
	int32_t *std_fds, t_minishell *shell)
{
	if (ct->commands->next == NULL)
		return (execute_simple_command(get_next_command(ct), shell));
	return (execute_pipeline(ct, std_fds, shell));
}

int32_t	executor(t_minishell *shell)
{
	t_command_table	*ct;
	int32_t			status;
	int32_t			std_fds[2];

	status = 0;
	ct = get_next_command_table(&shell->ast);
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (ct)
	{
		status = execute_command_table(ct, std_fds, shell);
		free(ct);
		ct = get_next_command_table(&shell->ast);
		dup2(std_fds[STDIN_FILENO], STDIN_FILENO);
		dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO);
	}
	close(std_fds[STDIN_FILENO]);
	close(std_fds[STDOUT_FILENO]);
	return (status);
}
