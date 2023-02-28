#include <minishell.h>

void	deconstruct_command_table(void *command_table)
{
	t_command_table	*ct;

	if (!command_table)
		return ;
	ct = (t_command_table *)command_table;
	ft_lstclear(&ct->commands, deconstruct_command);
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
// There should actually also be a datastructure for the ast that keeps track of the head of the ct
void	get_one_command_table(t_list **ast, t_command_table **ct)
{
	if (!*ast)
		return ;
	*ct = (*ast)->content;
}

t_command_table	*construct_command_table(t_list **tokens)
{
	t_command_table	*command_table;
	t_command		*command;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
	{
		command = construct_command(tokens);
		if (!command || !ft_lstadd_backnew(&command_table->commands, command))
		{
			deconstruct_command_table(command_table);
			deconstruct_command(command);
			return (NULL);
		}
		command_table->n_commands++;
	}
	command_table->commands_head = command_table->commands;
	return (command_table);
}
