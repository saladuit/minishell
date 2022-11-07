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
}

pid_t	execute_command(int32_t in_fd, int32_t out_fd, t_command *command, char **envp)
{
	pid_t	pid;
	t_redir	*redir;
	char	*command_path;
	char	**arguments;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	if (in_fd != -1 && !protected_dup2(in_fd, INPUT))
		exit(errno);
	if (out_fd != -1 && !protected_dup2(out_fd, OUTPUT))
		exit(errno);
	redir = get_next_redir(command);
	while (redir)
	{
		if (redir->type == INPUT)
		{
			if (in_fd != -1)
				close(in_fd);
			if (!open_redir(&in_fd, redir->filename, INPUT))
				exit(errno);
		}
		if (redir->type == OUTPUT)
		{
			if (out_fd != -1)
				close(out_fd);
			if (!open_redir(&out_fd, redir->filename, OUTPUT))
				exit(errno);
		}
		redir = get_next_redir(command);
	}
	arguments = get_arguments(command);
	command_path = get_cmd_path(envp, arguments[0]);
	if (access(command_path, X_OK))
		printf("%s: %s: %s\n", "Minishell", arguments[0], "Command not found");
	execve(command_path, arguments, envp);
	exit(errno);
}

int32_t	run_commands(t_command_table *ct, char **envp)
{
	int32_t		pipe_fds[2];
	t_command	*command;
	int32_t		in_fd;
	int32_t		out_fd;
	pid_t		pid;

	in_fd = -1;
	out_fd = -1;
	command = get_next_command(ct);
	while (command)
	{
		// print_command(command);
		if (ct->commands)
		{
			if (pipe(pipe_fds) == -1)
				return (ERROR);
			out_fd = pipe_fds[1];
		}
		pid = execute_command(in_fd, out_fd, command, envp);
		close(out_fd);
		out_fd = -1;
		if (in_fd != -1)
			close(in_fd);
		in_fd = pipe_fds[0];
		command = get_next_command(ct);
	}
	close(in_fd);
	return (pid);
}

// pid_t	run_command(char **arguments, char **envp)
// {
// 	char	*command_path;
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid != 0)
// 		return (pid);
// 	command_path = get_cmd_path(envp, arguments[0]);
// 	execve(command_path, arguments, envp);
// 	return (pid);
// }

int32_t	executor(t_list *ast, char **envp)
{
	t_command_table	*ct;
	// t_command	*command;
	// char			**arguments;
	// t_redir		*redir;
	int32_t status;
	pid_t pid;

	(void)envp;
	status = 0;
	ct = get_next_command_table(&ast);
	while (ct)
	{
		// while (command)
		// {
		// 	arguments = get_arguments(command);
		// 	// redir = get_next_redir(command);
		// 	pid = run_command(arguments, envp);
		// 	ft_matrixfree(&arguments);
		// 	free(command);
		// 	command = get_next_command(ct);
		// }
		pid = run_commands(ct, envp);
		waitpid(pid, &status, WUNTRACED);
		wait(NULL);
		free(ct);
		ct = get_next_command_table(&ast);
	}
	return (WEXITSTATUS(status));
}
