#ifndef COMMAND_H
# define COMMAND_H
# include <libft.h>
# include <stdint.h>
# include <redir.h>
# include <message.h>
# include <minitype.h>


typedef struct s_command
{
	int32_t	arg_count;
	char	**arguments;
	t_list	*redir;
}	t_command;

t_command	*deconstruct_command(t_command **command);
t_command	*clear_get_command(t_command **command, t_list **arguments);
void		clean_command(void *ptr);
t_command	*get_command(t_list **tokens);

#endif
