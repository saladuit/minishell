#ifndef ARGUMENT
# define ARGUMENT

# include <stdlib.h>
# include <command.h>
# include <message.h>

int32_t	fill_arguments(t_command *command, t_list **arg_list);
t_list	*add_argument(t_list **tokens, t_command *command, t_list **arguments);
#endif
