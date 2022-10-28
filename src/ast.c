#include <ast.h>

static void	command_clear_hook(void *ptr)
{
	t_command	*command;

	command = ptr;
	deconstruct_command(&command);
}

void	deconstruct_ast(t_list **ast)
{
	t_command_table	*command_table;

	while (*ast)
	{
		command_table = (*ast)->content;
		ft_lstclear(&command_table->commands, command_clear_hook);
		ft_lstclear(ast, free);
		*ast = (*ast)->next;
	}
}

t_list	*construct_ast(t_list *tokens)
{
	t_list	*ast;

	ast = NULL;
	while (tokens)
	{
		if (!ft_lstadd_backnew(&ast, (void *)construct_command_table(&tokens)))
			ft_minishell_exit(EMALLOC);
	}
	return (ast);
}
