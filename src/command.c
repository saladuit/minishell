#include <command.h>

t_command	*deconstruct_command(t_command **command)
{
	char	*filename;
	t_redir	*redir;

	if ((*command)->redirs)
	{
		redir = (*command)->redirs->content;
		filename = redir->filename;
		free(filename);
		free(redir);
	}
	ft_lstclear(&(*command)->arguments, free);
	ft_lstclear(&(*command)->redirs, free);
	free(*command);
	*command = NULL;
	return (NULL);
}

char	*get_next_argument(t_list	**arguments)
{
	char	*argument;

	if (!arguments)
		ft_minishell_exit(EREQUEST);
	if (!*arguments)
		return (NULL);
	argument = (*arguments)->content;
	*arguments = (*arguments)->next;
	return (argument);
}
t_redir	*get_next_redir(t_list	**redirs)
{
	t_redir	*redir;

	if (!redirs)
		ft_minishell_exit(EREQUEST);
	if (!*redirs)
		return (NULL);
	redir = (*redirs)->content;
	*redirs = (*redirs)->next;
	return (redir);
}
t_command	*get_next_command(t_list **command)
{
	t_command	*next_command;

	if (!command)
		ft_minishell_exit(EREQUEST);
	if (!*command)
		return (NULL);
	next_command = (*command)->content;
	*command = (*command)->next;
	return (next_command);
}

t_command	*construct_command(t_list **tokens)
{
	t_command	*command;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		ft_minishell_exit(EMALLOC);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (ft_isdelimiter(*token))
			break ;
		if (ft_isredir(*token) && !ft_lstadd_backnew(&command->redirs, construct_redir(tokens)))
				ft_minishell_exit(EMALLOC);
		else if (!ft_lstadd_backnew(&command->arguments, (*tokens)->content))
				ft_minishell_exit(EMALLOC);
		*tokens = (*tokens)->next;
	}
	return (command);
}
