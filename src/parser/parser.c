#include <minishell.h>

t_list	*parser(t_list *tokens)
{
	t_list	*ast;

	ast = construct_ast(tokens);
	if (!ast)
		return (NULL);
	return (ast);
}
