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
	if (redir->type == HEREDOC)
	{
		make_heredoc();
	}
	else
	{
		redir->filename = (*tokens)->content;
	}
	*tokens = (*tokens)->next;
	return (redir);
}
