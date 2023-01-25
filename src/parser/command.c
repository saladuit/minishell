#include <minishell.h>


void	deconstruct_redirs(void *redir)
{
	t_redir *rdr;

	rdr = (t_redir *)redir;
	free(rdr->filename);
	free(rdr);
}

void	deconstruct_command(void *command)
{
	t_command *cmd;

	cmd = (t_command *)command;
	ft_lstclear(&cmd->arguments, free);
	ft_lstclear(&cmd->redirs, deconstruct_redirs);
	free(cmd);
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
	return (arguments);
}

t_redir	*get_next_redir(t_command *cmd)
{
	t_redir	*current;

	if (!cmd->redirs)
		return (NULL);
	current = cmd->redirs->content;
	cmd->redirs = cmd->redirs->next;
	return (current);
}

t_command	*get_next_command(t_command_table *ct)
{
	t_command	*current;

	if (!ct->commands)
		return (NULL);
	current = ct->commands->content;
	ct->commands = ct->commands->next;
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
