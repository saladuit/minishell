#include <parser.h>

t_list *parser(t_list *tokens)
{
	t_list *ast;

	ast = construct_ast(tokens);
	if (!ast)
		ft_minishell_exit(EMALLOC);
	return (ast);
}
