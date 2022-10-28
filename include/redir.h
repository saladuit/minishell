#ifndef REDIR_H
# define REDIR_H
# include <stdlib.h>
# include <libft.h>

typedef enum e_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_redir
{
	char	*filename;
	t_type	type;
}	t_redir;

t_redir	*construct_redir(t_list **tokens);
t_list	*deconstruct_redir(t_redir **redir);

#endif
