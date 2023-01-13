#include <minishell.h>

char	**get_arguments(t_command *cmd)
{
	t_list	*tmp;
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
		tmp = cmd->arguments;
		cmd->arguments = cmd->arguments->next;
		free(tmp);
		i++;
	}
	return (arguments);
}

t_redir	*get_next_redir(t_command *cmd)
{
	t_redir	*current;
	t_list	*tmp;

	if (!cmd->redirs)
		return (NULL);
	current = cmd->redirs->content;
	tmp = cmd->redirs;
	cmd->redirs = cmd->redirs->next;
	free(tmp);
	return (current);
}

t_command	*get_next_command(t_command_table *ct)
{
	t_command	*current;
	t_list		*tmp;

	if (!ct->commands)
		return (NULL);
	current = ct->commands->content;
	tmp = ct->commands;
	ct->commands = ct->commands->next;
	free(tmp);
	return (current);
}

t_command	*construct_command(t_list **tokens)
{
	t_command	*command;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (is_delimiter(*token))
		{
			*tokens = (*tokens)->next;
			break ;
		}
		if (!is_redir(*token)
			&& !ft_lstadd_backnew(&command->arguments,
				ft_strdup((*tokens)->content)))
      return (NULL);
		if (is_redir(*token)
			&& !ft_lstadd_backnew(&command->redirs, construct_redir(tokens)))
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (command);
}
