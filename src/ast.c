#include <ast.h>

void	deconstruct_ast(t_list **ast)
{
	t_command_table	*command_table;

	command_table = (*ast)->content;
	ft_lstclear(&command_table->commands, clean_command);
	ft_lstclear(ast, free);
}

t_list	*construct_ast(t_list *tokens)
{
	t_list	*ast;

	ast = NULL;
	while (tokens)
	{
		if (!ft_lstadd_backnew(&ast, (void *)get_command_table(&tokens)))
		{
			ft_lstclear(&ast, free);
			return (NULL);
		}
	}
	return (ast);
}
