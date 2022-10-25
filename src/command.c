#include <command.h>
#include <argument.h>

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

t_command	*clear_get_command(t_command **command, t_list **arguments)
{
	deconstruct_command(command);
	ft_lstclear(arguments, free);
	return (NULL);
}

void	clean_command(void *ptr)
{
	t_command	*command;

	command = ptr;
	deconstruct_command(&command);
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
