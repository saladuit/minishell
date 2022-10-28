#include <command_table.h>

t_command_table	*get_next_command_table(t_list **ast)
{
	t_command_table	*next_ct;

	if (!ast)
		ft_minishell_exit(EREQUEST);
	if (!*ast) 
		return (NULL);
	next_ct = (*ast)->content;
	*ast = (*ast)->next;
	return (next_ct);
}

t_command_table	*construct_command_table(t_list **tokens)
{
	t_command_table	*command_table;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		ft_minishell_exit(EMALLOC);
	while (*tokens)
	{
		if (!ft_lstadd_backnew(&command_table->commands, construct_command(tokens)))
			ft_minishell_exit(EMALLOC);
		*tokens = (*tokens)->next;
		command_table->command_count++;
	}
	return (command_table);
}
