#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>

# include <libft.h>
# include <ast.h>
# include <message.h>

/**
 *  @brief Converts tokens into an Abstract Syntax Tree.
 *  Exits program on failure.
 *
 *  An Abstract Syntax Tree is a linked list of chained command tables.
 *  Each command table is delimited by:
 *  - ;
 *  - &&
 *  - ||
 *  A command table contains a counter to keep track of the amount of commands
 *  and a linked list of commands.
 *
 *  A command consists out of arguments and redirections and
 *  a counter for the amount of arguments.
 *
 *  The redirections have their own structure containing a filename and type.
 *
 *  The Data Structures used are defined in command_table.h & command.h respectively.
 *
 *  The parser provides interfaces to better communicate with this data structure.
 *  These are defined in the astapi.h
 *  - Iterating to the next command table.
 *  - Iterating to the next command.
 *  - Getting the command arguments.
 *  - Getting the next redirection struct.
 *
 *  @param ast		-	Empty linked list
 *  @param tokens	-	The tokens to be placed incside the AST
 *
 *  @return 		- The constructed AST
 */
t_list	*parser(t_list *tokens);

#endif
