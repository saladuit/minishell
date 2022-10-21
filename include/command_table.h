#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include <libft.h>
# include <stdint.h>
# include <command.h>
# include <message.h>

typedef struct s_command_table {
    int32_t command_count;
    t_list* commands;
}	t_command_table;

t_command_table	*get_command_table(t_list **tokens)
#endif
