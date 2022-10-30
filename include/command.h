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
 * @brief Constructs a command from 
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */

t_command	*construct_command(t_list **tokens);

#endif
