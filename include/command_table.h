#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

typedef struct s_command
{
	int32_t	arg_count;
	t_list	*tokens;
}	t_command;

void	insert_argument(char *argument);

typedef struct s_command_table
{
	int32_t		command_count;
	t_list		*commands;
	char		*out_file;
	char		*input_file;
	char		*err_file;
}	t_command_table;

void	insert_simple_command(t_command *command);

//void	prompt(void);
//void	print(void);
//void	execute(void);
//void	clear(void);

#endif
