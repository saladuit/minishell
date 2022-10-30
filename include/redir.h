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

/*
 * @brief contructs a redirection struct out of two tokens
 * the first token will become the redirection type and the second
 * whill become the filname
 *
 * @param command	-	Linked list with tokens
 * @return 			-	Redirection struct
 */

t_redir	*construct_redir(t_list **tokens);

#endif
