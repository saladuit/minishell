#include <ast.h>

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
