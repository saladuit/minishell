#include <command_table.h>
#include <builtins.h>
#include "minishell.h"
#include <executor.h>
#include <message.h>
#include <redir.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <astapi.h>

int32_t	redirect(t_redir *redir, t_type type)
{
	if (!open_redir(redir->filename, type))
		return (ERROR);
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

int32_t	execute_builtin(char **arguments, char **envp)
{
	t_builtin	builtin_function;

	builtin_function = builtin_lookup(arguments[0]);
	if (builtin_function.name == NULL)
		return (-1);
	return (builtin_function.func(arguments, envp));
}

int32_t	wait_for_child_processes(pid_t pid)
{
	int32_t	status;
	// t_list	*tmp_pids;

	// tmp_pids = pids;
	// while (pids)
	// {
	// 	waitpid(*(int *)pids->content, &status, WUNTRACED);
	// 	pids = pids->next;
	// }
	// ft_lstclear(&tmp_pids, free);
	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) != -1 && errno != ECHILD)
		;
	return (WEXITSTATUS(status));
}

int32_t	execute_command(t_command *cmd, char **envp)
{
	int32_t	status;
	char	**arguments;
	char	*command_path;

	arguments = get_arguments(cmd);
	status = execute_builtin(arguments, envp);
	setup_redirects(cmd);
	free(cmd);
	if (status >= 0)
		return (status);
	command_path = get_cmd_path(envp, arguments[0]);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found");
	execve(command_path, arguments, envp);
	exit(errno);
}

int32_t	execute_simple_command(t_command *cmd, char **envp)
{
	pid_t		pid;
	int32_t		status;
	char		*command_path;
	char		**arguments;

	arguments = get_arguments(cmd);
	setup_redirects(cmd);
	free(cmd);
	status = execute_builtin(arguments, envp);
	if (status >= 0)
		return (status);
	pid = fork();
	if (pid != 0)
		return (wait_for_child_processes(pid));
	command_path = get_cmd_path(envp, arguments[0]);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found");
	execve(command_path, arguments, envp);
	exit(errno);
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

int32_t	prepare_next_pipe(int32_t *pipe_fds)
{
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[0]);
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[1]);
	return (SUCCESS);
}

int32_t	execute_pipeline(t_command_table *ct, int32_t *std_fds, char **envp)
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
			execute_command(cmd, envp);
		// ft_lstadd_backnew(&pids, (void *)&pid);
		free(cmd);
		cmd = get_next_command(ct);
		if (ct->commands)
			prepare_next_pipe(pipe_fds);
		else if (cmd)
		{
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
				return (ERROR);
			close(pipe_fds[0]);
			if (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
				return (ERROR);
		}
	}
	return (wait_for_child_processes(pid));
}

int32_t	execute_command_table(t_command_table *ct, int32_t *std_fds, char **envp)
{
	if (ct->commands->next == NULL)
		return (execute_simple_command(get_next_command(ct), envp));
	return (execute_pipeline(ct, std_fds, envp));
}

int32_t	executor(t_list *ast, char **envp)
{
	t_command_table	*ct;
	int32_t			status;
	int32_t			std_fds[2];

	status = 0;
	ct = get_next_command_table(&ast);
	while (ct)
	{
		std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
		std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
		status = execute_command_table(ct, std_fds, envp);
		free(ct);
		ct = get_next_command_table(&ast);
		dup2(std_fds[STDIN_FILENO], STDIN_FILENO);
		dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO);
		close(std_fds[STDIN_FILENO]);
		close(std_fds[STDOUT_FILENO]);
	}
	return (status);
}
