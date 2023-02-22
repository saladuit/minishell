#include <minishell.h>

void			print_arguments(t_command *cmd)
{
	char	**arguments;
	int32_t	i;

	arguments = get_arguments(cmd);
	i = 0;
	if (!arguments)
		return ;
	while (arguments[i])
	{
		printf("\t\tArgument #%d: %s\n", i + 1, arguments[i]);
		i++;
	}
	free(arguments);
}

char	**get_arguments(t_command *cmd)
{
	char	**arguments;
	int32_t	i;

	if (!cmd->arguments)
		return (NULL);
	arguments = ft_calloc(ft_lstsize(cmd->arguments) + 1, sizeof(char *));
	if (!arguments)
		return (NULL);
	i = 0;
	while (cmd->arguments)
	{
		arguments[i] = cmd->arguments->content;
		cmd->arguments = cmd->arguments->next;
		i++;
	}
	cmd->arguments = cmd->arguments_head;
	return (arguments);
}
