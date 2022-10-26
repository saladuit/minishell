#include <executor.h>
#include <message.h>
#include <command.h>
#include <command_table.h>
#include <redir.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t	execute_process(int32_t in_fd, int32_t out_fd, t_command *command, char **envp)
{
	pid_t	pid;
	char	*command_path;
	char	*infile;
	char	*outfile;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	// printf("start child\n");
	signal(SIGINT, SIG_DFL);
	infile = get_redir_file(command, INPUT);
	outfile = get_redir_file(command, OUTPUT);
	if (infile)
	{
		if (in_fd != -1)
			close(in_fd);
		if (!open_redir(&in_fd, infile, INPUT))
			exit(errno);
	}
	else if (in_fd != -1 && !protected_dup2(in_fd, INPUT))
		exit(errno);
	// printf("input\n");
	if (outfile)
	{
		if (out_fd != -1)
			close(out_fd);
		if (!open_redir(&out_fd, outfile, OUTPUT))
			exit(errno);
	}
	else if (out_fd != -1 && !protected_dup2(out_fd, OUTPUT))
		exit(errno);
	// printf("output");
	command_path = get_cmd_path(envp, command->arguments[0]);
	execve(command_path, command->arguments, envp);
	exit(errno);
}

t_command	*get_command_index(t_command_table *command_table, int32_t index)
{
	int32_t		i;
	t_list		*commands;

	commands = command_table->commands;
	i = 0;
	while (i <= index && commands)
	{
		i++;
		commands = commands->next;
	}
	if (commands)
		return ((t_command *)commands->content);
	else
		return (NULL);
}

int32_t	run_commands(t_list *commands, char **envp)
{
	int32_t		pipe_fds[2];
	t_command	*command;
	int32_t		in_fd;
	int32_t		out_fd;
	pid_t		pid;

	in_fd = -1;
	out_fd = -1;
	while (commands)
	{
		if (commands->next)
		{
			if (pipe(pipe_fds) == -1)
				return (ERROR);
			out_fd = pipe_fds[1];
		}
		command = (t_command *)commands->content;
		// printf("in out fds: %i, %i\n", in_fd, out_fd);
		pid = execute_process(in_fd, out_fd, command, envp);
		close(out_fd);
		if (in_fd != -1)
			close(in_fd);
		in_fd = pipe_fds[0];
		commands = commands->next;
	}
	close(in_fd);
	return (pid);
}

int32_t	executor(t_list *abstract_syntax_tree, char **envp)
{
	t_command_table	*command_table;
	pid_t			pid;
	int32_t			status;

	// printf("table\n");
	command_table = (t_command_table *)abstract_syntax_tree->content;
	// printf("run\n");
	pid = run_commands(command_table->commands, envp);
	waitpid(pid, &status, WUNTRACED);
	wait(NULL);
	return (WEXITSTATUS(status));
}
