#include <command.h>

t_command	*deconstruct_command(t_command **command)
{
	char	*filename;
	t_redir	*redir;

	if ((*command)->redir)
	{
		redir = (*command)->redir->content;
		filename = redir->filename;
		free(filename);
		free(redir);
	}
	ft_matrixfree(&(*command)->arguments);
	ft_lstclear(&(*command)->redir, free);
	free(*command);
	*command = NULL;
	return (NULL);
}

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

t_command	*clear_get_command(t_command **command, t_list **arguments)
{
	deconstruct_command(command);
	ft_lstclear(arguments, free);
	return (NULL);
}

t_command	*get_command(t_list **tokens)
{
	t_command	*command;
	t_list		*arguments;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	arguments = NULL;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (ft_isdelimiter(*token))
			break ;
		if (ft_isredir(*token) && !add_redir(tokens, &command->redir))
			return (clear_get_command(&command, &arguments));
		else if (!add_argument(tokens, command, &arguments))
			return (clear_get_command(&command, &arguments));
	}
	if (fill_arguments(command, &arguments) == ERROR)
		return (clear_get_command(&command, &arguments));
	return (command);
}
