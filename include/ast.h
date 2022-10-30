#ifndef AST_H
# define AST_H

# include <libft.h>
# include <command_table.h>

/*
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */

t_list	*construct_ast(t_list *tokens);

# endif
