#include "libft.h"
#include <minishell.h>

void	deconstruct_ast(t_list **ast)
{
	ft_lstclear(ast, deconstruct_command_table);
	*ast = NULL;
}

void	debug_ast(t_list *ast)
{
	ft_putendl_fd("", 1);
	print_command_tables(ast);
	ft_putendl_fd("", 1);
}

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
