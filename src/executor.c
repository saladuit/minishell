#include <command_table.h>
#include <builtins.h>
#include "minishell.h"
#include <builtins.h>
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

void	print_command(t_command *command)
{
	char	**arguments;
	t_redir	*redir;
	int32_t	i;

	arguments = get_arguments(command);
	printf("Command: %s\n", arguments[0]);
	printf("arguments:\n");
	i = 0;
	while (arguments[i])
	{
		printf("	%s\n", arguments[i]);
		i++;
	}
	printf("redirects:\n");
	redir = get_next_redir(command);
	while (redir)
	{
		if (redir->type == INPUT)
			printf("Type: INPUT\n");
		else
			printf("Type: OUTPUT\n");
		printf("Filename: %s\n", redir->filename);
		redir = get_next_redir(command);
	}
}

void	setup_redirects(t_command *command, int32_t *in_fd, int32_t *out_fd)
{
	t_redir	*redir;

	redir = get_next_redir(command);
	while (redir)
	{
		if (redir->type == INPUT)
		{
			close(*in_fd);
			if (!open_redir(in_fd, redir->filename, INPUT))
				exit(errno);
		}
		if (redir->type == OUTPUT)
		{
			close(*out_fd);
			if (!open_redir(out_fd, redir->filename, OUTPUT))
				exit(errno);
		}
		free(redir);
		redir = get_next_redir(command);
	}
}

pid_t	execute_command(int32_t in_fd, int32_t out_fd, t_command *command, char **envp)
{
	pid_t	pid;
	char	*command_path;
	char	**arguments;

	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	if (!protected_dup2(in_fd, INPUT) || !protected_dup2(out_fd, OUTPUT))
		exit(errno);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found");
	execve(command_path, arguments, envp);
	exit(errno);
}

int32_t	pipe_commands(t_command_table *ct, char **envp)
{

	while (command)
	{
		if (ct->commands)
		{
			if (pipe(pipe_fds) == -1)
				return (ERROR);
			out_fd = pipe_fds[1];
		}
		pid = execute_command(in_fd, out_fd, command, envp);
		close(out_fd);
		out_fd = dup(STDOUT_FILENO);
		close(in_fd);
		in_fd = pipe_fds[0];
	}
	close(in_fd);
	return (pid);
}


t_builtin 	lookup_builtin(char *cmd)
{
	int const static lookup[] = 
	{.name = "echo", .builtin = ft_echo},
	{.name = "cd", .builtin = ft_cd},
	{.name = "pwd", .builtin = ft_pwd},
	{.name = "export", .builtin = ft_export},
	{.name = "unset", .builtin = ft_unset},
	{.name = "env", .builtin = ft_env},
	{.name = "exit", .builtin = ft_exit},
	{.name = NULL, .builtin = NULL};
	int32_t i;

	i = 0;
	while (ft_strncmp(lookup[i++].name, cmd, ft_strlen(cmd)))
	{
		if (lookup[i].name == NULL)
			return (NULL);
	}
	return (lookup[i]);
}

int32_t execute_simple_command(t_command_table *ct, char **envp)
{
	t_command	cmd;
	pit_t		pid;
	char	*command_path;
	char	**arguments;

	cmd = get_next_command(ct);
	arguments = get_arguments(cmd);
	if (is_builtin_command(arguments[i]))
		return (execute_builtin(arguments, envp));
	command_path = get_cmd_path(envp, arguments[0]);
	pid = fork();
	if (pid != 0)
		return (pid);
	setup_redirects(command, &in_fd, &out_fd);
}

int32_t	wait_for_child_processes(t_list *pids)
{
	int32_t status;

	while (pids)
	{
		waitpid(*(int *)pids->content, &status, WUNTRACED);
		pids = pids->next;
	}
	ft_lstclear(&pids, free);
	return (WEXITSTATUS(status));
}

int32_t	init_fds(int32_t *pipe_fds, int32_t *std_fds)
{
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (std_fds[STDIN_FILENO] == ERROR || std_fds[STDOUT_FILENO] == ERROR)
		return (ERROR);
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	return (SUCCESS);
}

int32_t execute_pipeline(t_command_table *ct, char **envp)
{
	t_command *cmd;
	int32_t	pipe_fds[2];
	int32_t	std_fds[2];
	int32_t status;
	t_list	*pids;

	if (init_fds(pipe_fds, std_fds)
			return (ERROR);
	cmd = get_next_command(ct);
	while (cmd)
	{
		free(cmd);
		cmd = get_next_command(ct);
	}
	return (wait_for_child_processes(pids));
}

int32_t	execute_command_table(t_command_table *ct, char **envp)
{
	if (ct->commands->next == NULL)
		return (execute_simple_command(ct, envp));
	return (execute_pipeline(ct, envp));
}

int32_t executor(t_list *ast, char **envp)
{
	t_command_table *ct;
	int32_t status;


	status = 0;
	ct = get_next_command_table(&ast);
	while (ct)
	{
		status = execute_command_table(ct, envp);
		free(ct);
		ct = get_next_command_table(&ast);
	}
	return (status);
}
