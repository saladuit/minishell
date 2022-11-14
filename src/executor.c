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

	arguments = get_arguments(command);
	if (is_builtin(arguments[0]))
		return (run_builtin(in_fd, out_fd, arguments, envp));
	command_path = get_cmd_path(envp, arguments[0]);
	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	if (!protected_dup2(in_fd, INPUT) || !protected_dup2(out_fd, OUTPUT))
		exit(errno);
	setup_redirects(command, &in_fd, &out_fd);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found");
	execve(command_path, arguments, envp);
	exit(errno);
}

int32_t	pipe_commands(t_command_table *ct, char **envp)
{
	int32_t		pipe_fds[2];
	t_command	*command;
	int32_t		in_fd;
	int32_t		out_fd;
	pid_t		pid;

	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	command = get_next_command(ct);
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
		free(command);
		command = get_next_command(ct);
	}
	close(in_fd);
	return (pid);
}

int32_t	executor(t_list *ast, char **envp)
{
	t_command_table	*ct;
	int32_t			status;
	pid_t			pid;

	status = 0;
	ct = get_next_command_table(&ast);
	while (ct)
	{
		pid = pipe_commands(ct, envp);
		waitpid(pid, &status, WUNTRACED);
		while (wait(NULL) != -1)
		{
		}
		free(ct);
		ct = get_next_command_table(&ast);
	}
	return (WEXITSTATUS(status));
}
