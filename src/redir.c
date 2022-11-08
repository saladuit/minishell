#include "message.h"
#include <redir.h>

t_type	set_type(char *symbol, size_t len)
{
	if (!ft_strncmp("<", symbol, len))
		return (INPUT);
	if (!ft_strncmp("<<", symbol, len))
		return (HEREDOC);
	if (!ft_strncmp(">", symbol, len))
		return (OUTPUT);
	return (APPEND);
}

t_redir	*construct_redir(t_list **tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		ft_minishell_exit(EMALLOC);
	redir->type = set_type((*tokens)->content, ft_strlen((*tokens)->content));
	*tokens = (*tokens)->next;
	redir->filename = (*tokens)->content;
	return (redir);
}
