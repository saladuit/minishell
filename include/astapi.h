#ifndef ASTAPI_H
# define ASTAPI_H

#include "command.h"
# include <ast.h>

/*
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */

char			**get_arguments(t_command *cmd);
t_redir			*get_next_redir(t_command *cmd);
t_command*		get_next_command(t_command_table *cmdt);
t_command_table *get_next_command_table(t_list **ast);


# endif
