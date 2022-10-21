#ifndef ARGUMENT
# define ARGUMENT

int32_t	fill_arguments(t_command *command, t_list **arg_list);
t_list	*add_argument(t_list **tokens, t_command *command, t_list **arguments);
#endif
