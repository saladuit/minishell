# include <argument.h>

int32_t	fill_arguments(t_command *command, t_list **arg_list)
{
	size_t	i;

	command->arguments = ft_calloc(command->arg_count + 1, sizeof(char *));
	if (!command->arguments)
		return (ERROR);
	i = 0;
	while (*arg_list)
	{
		command->arguments[i] = ft_strdup((*arg_list)->content);
		if (!command->arguments[i])
		{
			ft_matrixfree(&command->arguments);
			return (ERROR);
		}
		arg_list = &(*arg_list)->next;
		i++;
	}
	return (SUCCESS);
}

t_list	*add_argument(t_list **tokens, t_command *command, t_list **arguments)
{
	t_list	*new_node;
	char	*argument;

	argument = ft_strdup((*tokens)->content);
	if (!argument)
		return (NULL);
	new_node = ft_lstadd_backnew(arguments, argument);
	if (!new_node)
	{
		free(argument);
		return (NULL);
	}
	command->arg_count++;
	*tokens = (*tokens)->next;
	return (new_node);
}
