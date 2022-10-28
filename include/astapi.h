#ifndef ASTAPI_H
# define ASTAPI_H

# include <ast.h>

/*
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */

char			*get_next_argument(t_list	**arguments);
t_redir			*get_next_redir(t_list	**redirs);
t_command*		get_next_command(t_list** commands);
t_command_table *get_next_command_table(t_list **ast);

void			deconstruct_ast(t_list **ast);

# endif
