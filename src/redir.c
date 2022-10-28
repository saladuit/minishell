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
	else
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
	redir->filename = ft_strdup((*tokens)->content);
	if (!redir->filename)
		ft_minishell_exit(EMALLOC);
	return (redir);
}

t_list	*deconstruct_redir(t_redir **redir)
{
	if ((*redir)->filename)
	{
		free((*redir)->filename);
		(*redir)->filename = NULL;
	}
	if (*redir)
	{
		free(*redir);
		*redir = NULL;
	}
	return (NULL);
}

