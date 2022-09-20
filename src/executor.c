#include <executor.h>
#include <message.h>
#include <command.h>
#include <unistd.h>
#include <libft.h>


pid_t	execute(char **args, char **envp)
{
	pid_t	pid;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	execv(args[0], args);
	_Exit(EXIT_FAILURE);
}

int32_t	executor(t_list *abstract_syntax_tree)
{
	t_command_table	*command_table;
	t_command		*command;
	char			*envp[] = {"", NULL};

	command_table = (t_command_table *)abstract_syntax_tree->content;
	command = command_table->commands->content;
	execute(command->arguments, envp);
	return (SUCCESS);
}
