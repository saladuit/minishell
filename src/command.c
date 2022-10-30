#include "command_table.h"
#include <command.h>

char	**get_arguments(t_command *cmd)
{
	t_list *tmp;
	char	**arguments;

	if (!cmd->arguments)
		ft_minishell_exit(EREQUEST);
	arguments = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	if (!arguments)
		ft_minishell_exit(EMALLOC);
	arguments[cmd->arg_count] = NULL;
	while (cmd->arguments)
	{
		*arguments = cmd->arguments->content;
		tmp = cmd->arguments;
		cmd->arguments = cmd->arguments->next;
		free(tmp);
	}
	return (arguments);
}

t_redir	*get_next_redir(t_command *cmd)
{
	t_redir	*next;
	t_list 	*tmp;

	if (!cmd->redirs)
		ft_minishell_exit(EREQUEST);
	tmp = cmd->redirs;
	cmd->redirs = cmd->redirs->next;
	if (cmd->redirs == NULL)
		return (NULL);
	next = tmp->content;
	free(tmp);
	return (next);
}

t_command	*get_next_command(t_command_table *ct)
{
	t_command	*next;
	t_list		*tmp;

	if (!ct->commands)
		ft_minishell_exit(EREQUEST);
	tmp = ct->commands;
	ct->commands = ct->commands->next;
	if (ct->commands == NULL)
		return (NULL);
	next = tmp->content;
	free(tmp);
	return (next);
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
		{
			*tokens = (*tokens)->next;
			break ;
		}
		if (ft_isredir(*token) && !ft_lstadd_backnew(&command->redirs, construct_redir(tokens)))
				ft_minishell_exit(EMALLOC);
		else if (!ft_lstadd_backnew(&command->arguments, (*tokens)->content))
				ft_minishell_exit(EMALLOC);
		*tokens = (*tokens)->next;
	}
	return (command);
}
