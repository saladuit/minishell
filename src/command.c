#include "command_table.h"
#include "libft.h"
#include <command.h>

char	**get_arguments(t_command *cmd)
{
	t_list	*tmp;
	char	**arguments;
	int32_t	i;

	if (!cmd)
		ft_minishell_exit(EREQUEST);
	if (!cmd->arguments)
		return (NULL);
	arguments = ft_calloc(ft_lstsize(cmd->arguments) + 1, sizeof(char *));
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

	if (!cmd)
		ft_minishell_exit(EREQUEST);
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

	if (!ct)
		ft_minishell_exit(EREQUEST);
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
