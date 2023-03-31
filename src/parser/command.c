#include <minishell.h>

void	deconstruct_command(void *command)
{
	t_command	*cmd;

	cmd = (t_command *)command;
	if (!cmd)
		return ;
	ft_lstclear(&cmd->arguments, free);
	ft_lstclear(&cmd->redirs, deconstruct_redirs);
	free(cmd);
}

void	print_commands(t_command_table *ct)
{
	t_command	*cmd;
	int32_t		i;

	i = 0;
	while (i < ct->n_commands)
	{
		get_next_command(ct, &cmd);
		i++;
		ft_printf("\tCommand #%d at %p\n", i, ct);
		print_arguments(cmd);
		print_redirs(cmd);
	}
}

void	get_next_command(t_command_table *ct, t_command **command)
{
	if (!ct->commands)
		return ;
	*command = ct->commands->content;
	if (ct->commands->next == NULL)
	{
		ct->commands = ct->commands_head;
		return ;
	}
	else
		ct->commands = ct->commands->next;
	return ;
}

t_command	*construct_command(t_list **tokens, t_status *status,
		t_dictionary *env)
{
	t_command	*command;
	t_redir		*redir;
	char		*argument;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (*tokens)
	{
		token = expand_token((*tokens)->content, status, env);
		if (is_pipe(*token) && ft_strlen(token) == 1)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		if (is_redir(*token))
		{
			redir = construct_redir(tokens, status, env);
			if (!redir || !ft_lstadd_backnew(&command->redirs, redir))
			{
				deconstruct_redirs(redir);
				deconstruct_command(command);
				return (NULL);
			}
			command->n_redirs++;
		}
		else
		{
			argument = ft_strdup((*tokens)->content);
			if (!argument || !ft_lstadd_backnew(&command->arguments, argument))
			{
				if (argument)
					free(argument);
				deconstruct_command(command);
				return (NULL);
			}
			command->n_arguments++;
		}
		*tokens = (*tokens)->next;
	}
	command->arguments_head = command->arguments;
	command->redirs_head = command->redirs;
	return (command);
}
