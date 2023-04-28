#include <minishell.h>


static int	open_heredoc(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	unlink(path);
	return (fd);
}

static int	open_input(char *path)
{
	return (open(path, O_RDONLY));
}

static int	open_output(char *path)
{
	return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664));
}

static int	open_append(char *path)
{
	return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0664));
}

static bool	open_fd_type(char *path, t_type type)
{
	assert(type < TYPE_COUNT);
	if (type == HEREDOC)
		return (open_heredoc(path));
	else if (type == INPUT)
		return (open_input(path));
	else if (type == OUTPUT)
		return (open_output(path));
	else
		return (open_append(path));
}
static int32_t redirect_file_descriptor(int source_fd, t_type redirection)
{
    int target_fd;
    if (redirection == INPUT || redirection == HEREDOC)
        target_fd = STDIN_FILENO;
    else
        target_fd = STDOUT_FILENO;
    return (dup2(source_fd, target_fd));
}

int32_t	redirect(t_redir *redir, t_type type)
{
	int32_t	fd;

	fd = open_fd_type(redir->filename, type);
	if (fd == ERROR)
		return (ERROR);
	if (redirect_file_descriptor(fd, type) == ERROR)
	{
		close(fd);
		return (ERROR);
	}
	return (SUCCESS);
}

static void close_fd_if_open(int32_t *fd)
{
  if (*fd != -1)
  {
    close(*fd);
    *fd = -1;
  }
}

static bool handle_redirection(t_redir *redir, int32_t *input_fd, int32_t *output_fd)
{
  int32_t ret;

  ret = redirect(redir, redir->type);
  if (ret == ERROR)
    return (false);
  if (redir->type == INPUT || redir->type == HEREDOC)
  {
    close_fd_if_open(input_fd);
    *input_fd = ret;
  }
  else
  {
    close_fd_if_open(output_fd);
    *output_fd = ret;
  }
  return (true);
}

int32_t setup_redirects(t_command *command)
{
  t_redir *redir;
  int32_t i;
  int32_t input_fd = -1;
  int32_t output_fd = -1;

  i = 0;
  while (i < command->n_redirs)
  {
    get_next_redir(command, &redir);
    if (!handle_redirection(redir, &input_fd, &output_fd))
    {
      close_fd_if_open(&input_fd);
      close_fd_if_open(&output_fd);
      return (message_system_call_error("redirect"));
    }
    i++;
  }
  return (SUCCESS);
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
	// close(STDIN_FILENO);
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

static bool	file_is_executable(char *path)
{
	return (access(path, X_OK) == SUCCESS);
}

static char	*search_cmd_in_path(const char *path, const char *cmd)
{
	char		**path_dirs;
	char		*cmd_path;
	size_t		i;

	path_dirs = ft_split(path, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		cmd_path = ft_strjoin(path_dirs[i], cmd);
		if (!cmd_path)
			break ;
		if (file_is_executable(cmd_path))
		{
			ft_matrixfree(&path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_matrixfree(&path_dirs);
	return (NULL);
}

char		*get_cmd_path(char *path, char *cmd)
{
	char	*cmd_path;

	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (file_is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	cmd_path = search_cmd_in_path(path, cmd);
	return (cmd_path);
}

void	execute_child_command(t_minishell *shell, char **arguments)
{
	char	*command_path;

	command_path = get_cmd_path(dict_get(&shell->env, "PATH"), arguments[0]);
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


int32_t handle_first_pipe(int32_t *pipe_fds)
{
    if (pipe(pipe_fds) == ERROR)
        return (ERROR);
    if (dup2(pipe_fds[1], STDOUT_FILENO) == ERROR)
        return (ERROR);
    return close(pipe_fds[1]);
}

int32_t handle_middle_pipes(int32_t *pipe_fds)
{
    if (dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
        return (ERROR);
    if (close(pipe_fds[STDIN_FILENO]) == ERROR)
        return (ERROR);
    if (pipe(pipe_fds) == ERROR)
        return (ERROR);
    if (dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
        return (ERROR);
    return close(pipe_fds[STDOUT_FILENO]);
}

int32_t handle_last_pipe(int32_t *pipe_fds, int32_t *std_fds)
{
    if (dup2(pipe_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
        return (ERROR);
    // if (close(pipe_fds[STDIN_FILENO]) == ERROR)
    //     return (ERROR);
    return dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO);
}

int32_t handle_pipes(int32_t *pipe_fds, int32_t *std_fds, int32_t n_commands, int32_t i)
{
		if (i == 0)
			return (handle_first_pipe(pipe_fds));
		else if (i == n_commands - 1)
			return (handle_last_pipe(pipe_fds, std_fds));
		return (handle_middle_pipes(pipe_fds));
}

int32_t process_command(int32_t *pipe_fds, t_command_table *ct, t_minishell *shell)
{
  t_command *cmd;
  pid_t pid;

  get_next_command(ct, &cmd);
  pid = fork();
  if (pid == -1)
		return (ERROR);
	if (pid == 0)
  {
    assert(close(pipe_fds[STDIN_FILENO]) == SUCCESS);
    execute_pipe_command(cmd, shell);
  }
  return (pid);
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
  		shell->status = message_general_error(E_GENERAL, "Executor: ");
  		break ;
  	}
  	pid = process_command(pipe_fds, ct, shell);
  	if (pid == ERROR)
  	{
  		shell->status = message_general_error(E_GENERAL, "Executor: ");
  		break ;
  	}
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
	assert(dup2(std_fds[STDIN_FILENO], STDIN_FILENO) >= SUCCESS);
	assert(dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) >= SUCCESS);
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
