#include <executor.h>
#include <message.h>
#include <command.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int32_t	check_path(char **args, char *path)
{
	char	*path_to_check;
	char	*path_suffix;
	int32_t	ret;

	ret = 0;
	path_suffix = ft_strjoin("/", args[0]);
	path_to_check = ft_strjoin(path, path_suffix);
	if (path_to_check && !access(path_to_check, X_OK))
		ret = 1;
	free(path_suffix);
	free(path_to_check);
	return (ret);
}

char	*get_command_path(char **args)
{
	char	**paths;
	char	*command_path;
	char	*command_suffix;
	int32_t	i;

	paths = ft_split(getenv("PATH"), ':');
	command_suffix = ft_strjoin("/", args[0]);
	i = 0;
	while (paths[i])
	{
		if (check_path(args, paths[i]))
		{
			command_path = ft_strjoin(paths[i], command_suffix);
			if (command_path)
			{
				free(command_suffix);
				return (command_path);
			}
		}
		i++;
	}
	return (ft_strdup(args[0]));
}

pid_t	execute(char *command_path, char **args, char **envp)
{
	pid_t	pid;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	execve(command_path, args, envp);
	exit(errno);
}

t_command	get_command(t_command_table *command_table, int32_t element)
{
	t_command	command;
	int32_t		i;
	t_list		*commands;

	commands = command_table->commands;
	i = 0;
	while (i <= element && commands)
	{
		i++;
		commands = commands->next;
	}
	if (commands)
		return ((t_command)commands->content);
	else
		return (NULL);
}

int32_t	run_commands(t_command_table *command_table, char **envp)
{
	int32_t		i;
	int32_t		*pipe_fds[2];
	t_command	command;
	int32_t		input;

	i = 0;
	while (i < command_table->command_count)
	{
		command = get_command(command_table, i);
		if (i > 0)
		{
			pipe(pipe_fds);
			execute_process(pipe_fds, command, envp);
		}
		i++;
	}
}

int32_t	executor(t_list *abstract_syntax_tree, char **envp)
{
	t_command_table	*command_table;
	char			**args;
	pid_t			pid;
	int32_t			status;
	t_command		*command;
	char			*command_path;

	command_table = (t_command_table *)abstract_syntax_tree->content;
	command = (t_command *)command_table->commands->content;
	args = command->arguments;
	command_path = get_command_path(args);
	pid = execute(command_path, args, envp);
	waitpid(pid, &status, WUNTRACED);
	if (status)
	{
		ft_printf("%s: %s: %i\n", command_path, strerror(status), status);
	}
	return (SUCCESS);
}
