#include <minishell.h>

t_command_table	*get_next_command_table(t_list **ast)
{
	t_command_table	*current;
	t_list			*tmp;

	if (!*ast)
		return (NULL);
	current = (*ast)->content;
	tmp = (*ast);
	*ast = (*ast)->next;
	free(tmp);
	return (current);
}

t_command_table	*construct_command_table(t_list **tokens)
{
	t_command_table	*command_table;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
	{
		if (!ft_lstadd_backnew(&command_table->commands, construct_command(tokens)))
			return (NULL);
		command_table->command_count++;
	}
	return (command_table);
}
