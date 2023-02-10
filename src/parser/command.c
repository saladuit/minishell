#include <minishell.h>

void deconstruct_command(void *command)
{
	t_command *cmd;

	cmd = (t_command *)command;
	ft_lstclear(&cmd->arguments, free);
	ft_lstclear(&cmd->redirs, deconstruct_redirs);
	free(cmd);
}

void print_commands(t_command_table *ct)
{
	t_command *cmd;
	int32_t	   i;

	cmd = get_next_command(ct);
	i	= 0;
	while (cmd)
	{
		i++;
		ft_printf("\tCommand #%d at %p\n", i, ct);
		print_arguments(cmd);
		print_redirs(cmd);
		cmd = get_next_command(ct);
	}
}

t_command *get_next_command(t_command_table *ct)
{
	t_command *current;

	if (!ct->commands)
		return (NULL);
	current = ct->commands->content;
	if (ct->end_reached == true)
	{
		ct->end_reached = false;
		return (NULL);
	}
	if (ct->commands->next == NULL)
	{
		ct->end_reached = true;
		ct->commands	= ct->commands_head;
	}
	else
		ct->commands = ct->commands->next;
	return (current);
}

t_command *construct_command(t_list **tokens)
{
	t_command *command;
	char	  *token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (is_delimiter(*token) && ft_strlen(token) == 1)
		{
			*tokens = (*tokens)->next;
			break;
		}
		if (!is_redir(*token) &&
			!ft_lstadd_backnew(&command->arguments,
							   ft_strdup((*tokens)->content)))
			return (NULL);

		if (is_redir(*token) &&
			!ft_lstadd_backnew(&command->redirs, construct_redir(tokens)))
			return (NULL);
		*tokens = (*tokens)->next;
	}
	command->arguments_head = command->arguments;
	command->redirs_head	= command->redirs;
	return (command);
}
