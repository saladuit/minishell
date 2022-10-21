#include <command_table.h>

t_command_table	*get_command_table(t_list **tokens)
{
	t_command_table	*command_table;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
	{
		if (!ft_lstadd_backnew(&command_table->commands, get_command(tokens)))
		{
			ft_lstclear(&command_table->commands, free);
			free(command_table);
			return (NULL);
		}
		command_table->command_count++;
	}
	return (command_table);
}
