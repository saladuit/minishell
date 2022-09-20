#include <executor.h>
#include <message.h>
#include <command.h>
#include <unistd.h>
#include <libft.h>

char	**get_args(t_command_table *command_table)
{
	char		**args;
	t_command	*command;
	char		**arguments;
	int32_t		i;

	command = (t_command *)command_table->commands->content;
	args = malloc(command->arg_count + 1);
	arguments = command->arguments;
	i = 0;
	while (i < command->arg_count)
	{
		args[i] = arguments[i];
	}
	args[i] = NULL;
	return (args);
}

pid_t	execute(char **args, char **envp)
{
	pid_t	pid;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	execve(args[0], args, envp);
	exit(EXIT_FAILURE);
}

int32_t	executor(t_list *abstract_syntax_tree)
{
	t_command_table	*command_table;
	char			**args;
	char			*envp[] = {NULL};

	command_table = (t_command_table *)abstract_syntax_tree->content;
	command = command_table->commands->content;
	execute(command->arguments, envp);
	return (SUCCESS);
}
