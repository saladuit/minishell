#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H

typedef struct s_simple_command
{
	int32_t	argument_count;
	char	**arguments;
}	t_simple_command;

void	insert_argument(char *argument);

typedef struct s_command
{
	int32_t				simple_command_count;
	t_simple_command	**simple_commands;
	char				*out_file;
	char				*input_file;
	char				*err_file;
	int32_t				background;
}

void	insert_simple_command(t_simple_command *simple_command);

void	prompt(void);
void	print(void);
void	execute(void);
void	clear(void);

#endif
