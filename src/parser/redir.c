#include <minishell.h>

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
		return (NULL);
	redir->type = set_type((*tokens)->content, ft_strlen((*tokens)->content));
	*tokens = (*tokens)->next;
	if (redir->type == HEREDOC)
	{
		redir->filename = add_heredoc((*tokens)->content);
		if (redir->filename == NULL)
			return (NULL);
	}
	else
	{
		redir->filename = ft_strdup((char *)(*tokens)->content);
	}
	return (redir);
}
