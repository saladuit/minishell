#include <minishell.h>

int32_t redirect(t_redir *redir, t_type type)
{
	if (!open_redir(redir->filename, type))
		return (handle_system_call_error("redirect"));
	return (SUCCESS);
}

int32_t setup_redirects(t_command *command)
{
	t_redir *redir;
	int32_t	 ret;
	int32_t		i;

	i = 0;
	while (i++ < command->n_redirs)
	{
		get_next_redir(command, &redir);
		ret = redirect(redir, redir->type);
	}
	return (ret);
}

t_builtin builtin_lookup(char *cmd)
{
	static const t_builtin lookup[] = {
		{.name = "echo",	 .func = ft_echo	},
		{.name = "cd",	   .func = ft_cd	},
		{.name = "pwd",	.func = ft_pwd	  },
		{.name = "export", .func = ft_export},
		{.name = "unset",  .func = ft_unset },
		{.name = "env",	.func = ft_env	  },
		{.name = "exit",	 .func = ft_exit	},
		{NULL,			   NULL			   }
	};
	int32_t i;

	i = 0;
	while (lookup[i].name != NULL &&
		ft_strncmp(lookup[i].name, cmd, ft_strlen(cmd) + 1))
		i++;
	return (lookup[i]);
}

int32_t execute_builtin(char **arguments, t_minishell *shell)
{
	t_builtin builtin_function;
	int32_t	  ret;

	builtin_function = builtin_lookup(arguments[0]);
	if (builtin_function.name == NULL)
		return (-1);
	ret = builtin_function.func(arguments, shell);
	return (ret);
}

int32_t wait_for_child_processes(pid_t pid)
{
	int32_t status;

	status = 0;
	close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) != -1 && errno != ECHILD)
		;
	if (g_exitcode == E_CTRL_C)
		return (E_CTRL_C);
	if (g_exitcode == S_EXEC_QUIT)
	{
		printf("Quit: 3\n");
		return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

void execute_child_command(t_minishell *shell, char **arguments)
{
	char *command_path;

	reset_signals();
	command_path = get_cmd_path(&shell->envd, arguments[0]);
	if (!command_path)
	{
		return;
	}
	if (access(command_path, X_OK))
	{
		write(2, "Minishell: ", 12);
		write(2, arguments[0], ft_strlen(arguments[0]));
		write(2, ": command not found\n", 21);
		free(command_path);
		return;
	}
	execve(command_path, arguments, dict_to_envp(&shell->envd));
	exit(127); // TODO make one func call
}

// Needs to always exit even if it is builtin
int32_t execute_pipe_command(t_command *cmd, t_minishell *shell)
{
	char  **arguments;
	int32_t status;

	reset_signals();
	status = setup_redirects(cmd);
	if (status)
		return (status);
	arguments = get_arguments(cmd);
	if (!arguments)
		return (1);
	status = execute_builtin(arguments, shell);
	if (status >= 0)
		return (status);
	// reset_signals();
	execute_child_command(shell, arguments);
	return (0);
}

int32_t execute_simple_command(t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	int32_t status;
	char  **arguments;

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
		execute_child_command(shell, arguments);
	free(arguments);
	return (wait_for_child_processes(pid));
}

int32_t init_first_pipe(int32_t *pipe_fds)
{
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[1]);
	// close(pipe_fds[0]);
	return (SUCCESS);
}

int32_t prepare_next_pipe(int32_t *pipe_fds, int32_t *std_fds, bool last)
{
	dup2(pipe_fds[0], STDIN_FILENO);
	// return (ERROR);
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

int32_t execute_pipeline(t_command_table *ct, int32_t *std_fds, t_minishell *shell)
{
	t_command *cmd;
	int32_t	   pipe_fds[2];
	pid_t	   pid;
	int32_t		i;

	if (init_first_pipe(pipe_fds) == -1)
		return (E_GENERAL);
	i = 0;
	while (i++ < ct->n_commands)
	{
		get_next_command(ct, &cmd);
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fds[0]);
			execute_pipe_command(cmd, shell);
		}
		if (!cmd)
			break;
		if (i == ct->n_commands)
			prepare_next_pipe(pipe_fds, std_fds, false);
		else
			prepare_next_pipe(pipe_fds, std_fds, true);
	}
	return (wait_for_child_processes(pid));
}

int32_t execute_command_table(
	t_command_table *ct, int32_t *std_fds, t_minishell *shell)
{
	t_command *cmd;

	if (ct->commands->next == NULL)
	{
		get_next_command(ct, &cmd);
		return (execute_simple_command(cmd, shell));
	}
	return (execute_pipeline(ct, std_fds, shell));
}

int32_t executor(t_minishell *shell)
{
	t_command_table *ct;
	int32_t			 status;
	int32_t			 std_fds[2];

//	setup_signals(SEXECUTOR);
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	get_one_command_table(&shell->ast, &ct);
	status = execute_command_table(ct, std_fds, shell);
	dup2(std_fds[STDIN_FILENO], STDIN_FILENO);
	dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO);
	close(std_fds[STDIN_FILENO]);
	close(std_fds[STDOUT_FILENO]);
	// setup_signals();
	return (status);
}
