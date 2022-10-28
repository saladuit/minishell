#ifndef COMMAND_H
# define COMMAND_H
# include <libft.h>
# include <stdint.h>
# include <redir.h>
# include <message.h>
# include <minitype.h>
# include <message.h>


typedef struct s_command
{
	int32_t	arg_count;
	t_list	*arguments;
	t_list	*redirs;
}	t_command;

/*
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */
t_command	*deconstruct_command(t_command **command);

/*
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */

t_command	*construct_command(t_list **tokens);

#endif
