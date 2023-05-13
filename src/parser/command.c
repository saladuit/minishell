/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parse_command.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:02 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:02 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

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

static int32_t	process_token(t_list **tokens, t_status *status,
		t_dictionary *env, t_command *command)
{
	char	*token;

	token = (*tokens)->content;
	if (is_pipe(*token))
	{
		return (SUCCESS);
	}
	if (is_redir(*token))
	{
		if (handle_redir(tokens, status, env, command) == ERROR)
			return (ERROR);
	}
	else
	{
		if (handle_argument(token, status, env, command) == ERROR)
			return (ERROR);
	}
	return (CONTINUE);
}

t_command	*construct_command(t_list **tokens, t_status *status,
		t_dictionary *env)
{
	t_command	*command;
	int32_t		result;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (*tokens)
	{
		result = process_token(tokens, status, env, command);
		if (result != CONTINUE)
		{
			if (result == SUCCESS)
				*tokens = (*tokens)->next;
			break ;
		}
		*tokens = (*tokens)->next;
	}
	if (result == ERROR)
	{
		deconstruct_command(command);
		return (NULL);
	}
	command->arguments_head = command->arguments;
	command->redirs_head = command->redirs;
	return (command);
}
