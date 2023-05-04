/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parse_command_table.c                           |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:06 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:06 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	deconstruct_command_table(void *command_table)
{
	t_command_table	*ct;

	if (!command_table)
		return ;
	ct = (t_command_table *)command_table;
	ft_lstclear(&ct->commands, deconstruct_command);
	free(ct->pids);
	free(ct);
}

void	print_command_tables(t_list *ast)
{
	t_command_table	*ct;
	int32_t			i;

	i = 1;
	get_one_command_table(&ast, &ct);
	printf("Command_table #%d at %p\n", i, ct);
	print_commands(ct);
}

void	get_one_command_table(t_list **ast, t_command_table **ct)
{
	*ct = (*ast)->content;
}

t_command_table	*construct_command_table(t_list **tokens, t_status *status,
		t_dictionary *env)
{
	t_command_table	*command_table;
	t_command		*command;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
	{
		command = construct_command(tokens, status, env);
		if (!command || !ft_lstadd_backnew(&command_table->commands, command))
		{
			deconstruct_command_table(command_table);
			deconstruct_command(command);
			return (NULL);
		}
		command_table->n_commands++;
	}
	command_table->pids = ft_calloc(command_table->n_commands, sizeof(pid_t));
	if (!command_table->pids)
		return (deconstruct_command_table(command_table), NULL);
	command_table->commands_head = command_table->commands;
	return (command_table);
}
