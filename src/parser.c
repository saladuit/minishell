#include <parser.h>

/* 
 *  The parser is responsible for going through the list of tokens
 *  and recognizing each one to construct an Abstract Syntax Tree.
 *
 *  An Abstract Syntax Tree is a linked list of chained command tables.
 *  Each command table is delimited by:
 *  - ;
 *  - && 
 *  - ||
 *  A command table contais the counter to keep track of the simple commands
 *  and a linked list of simple commands.
 *
 *  A simple command consists out of arguments and redirections and 
 *  a counter for the amount of arguments. 
 *
 *  This Data Structure is defined in command_table.h & command.h respectively.
 *  
 *  The parser provides interfaces to better communicate with this data structure.
 *  These are defined in their respecitve headers and include:
 *  - Iterating to the next command table.
 *  - Iterating to the next simple command
 *  - Getting the next array of arguments 
 *  - Getting the next list of redirections
 */

int32_t parser(t_list **ast, t_list *tokens)
{
	*ast = construct_ast(tokens);
	if (!*ast)
	{
		ft_lstclear(&tokens, free);
		return (ERROR);
	}
	return (SUCCESS);
}
