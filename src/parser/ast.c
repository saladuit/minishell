#include <minishell.h>

t_list	*construct_ast(t_list *tokens)
{
	t_list	*ast;

	if (tokens == NULL)
		return (NULL);
	ast = NULL;
	while (tokens)
	{
		if (!ft_lstadd_backnew(&ast, (void *)construct_command_table(&tokens)))
			return (NULL);
	}
	return (ast);
}

void	deconstruct_ast(t_list **ast)
{
	ft_lstclear(ast, deconstruct_command_table);
	*ast = NULL;
}
