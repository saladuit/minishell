/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parse_ast.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:34:58 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:34:58 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

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

t_list	*construct_ast(t_list *tokens, t_status *status, t_dictionary *env)
{
	t_command_table	*command_table;
	t_list			*ast;

	ast = NULL;
	while (tokens)
	{
		command_table = construct_command_table(&tokens, status, env);
		if (!command_table || !ft_lstadd_backnew(&ast, command_table))
		{
			deconstruct_command_table(command_table);
			deconstruct_ast(&ast);
			return (NULL);
		}
	}
	return (ast);
}
