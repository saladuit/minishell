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
}

t_list	*construct_ast(t_list *tokens)
{
	t_command_table	*command_table;
	t_list			*ast;

	if (tokens == NULL)
		return (NULL);
	ast = NULL;
	while (tokens)
	{
		command_table = construct_command_table(&tokens);
		if (!command_table || !ft_lstadd_backnew(&ast, command_table))
		{
			deconstruct_command_table(command_table);
			deconstruct_ast(&ast);
			return (NULL);
		}
	}
	return (ast);
}
