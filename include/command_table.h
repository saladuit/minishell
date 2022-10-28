#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

# include <libft.h>
# include <stdint.h>
# include <message.h>
# include <command.h>

typedef struct s_command_table
{
    int32_t	command_count;
    t_list*	commands;
}	t_command_table;


/*
 * @brief Returns a Command Table  made from the tokens provides. 
 * Exits on failure
 * 
 * @param ast		-	Abstract Syntax Tree to iterate over
 * @return 			-	Constructed Command Table
 */

t_command_table	*construct_command_table(t_list **tokens);

#endif
