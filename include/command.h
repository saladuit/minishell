#ifndef COMMAND_H
# define COMMAND_H
# include <libft.h>
# include <stdint.h>

typedef enum e_type
{
	DEFAULT,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
	END
}	t_type;

typedef struct s_redir
{
	char	*filename;
	t_type	type;
}	t_redir;

typedef struct s_command
{
	int32_t	arg_count;
	char	**arguments;
	t_list	*redir;
}	t_command;

typedef struct s_command_table
{
	int32_t	command_count;
	t_list	*commands;
}	t_command_table;

#endif
