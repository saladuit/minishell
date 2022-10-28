#ifndef AST_H
# define AST_H

# include <libft.h>
# include <command_table.h>

void	deconstruct_ast(t_list **ast);
t_list	*construct_ast(t_list *tokens);

# endif
