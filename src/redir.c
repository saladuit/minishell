#include <redir.h>

t_redir	*construct_redir(t_list **tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (!ft_strncmp("<", (*tokens)->content, 2))
		redir->type = INPUT;
	if (!ft_strncmp("<<", (*tokens)->content, 3))
		redir->type = HEREDOC;
	if (!ft_strncmp(">", (*tokens)->content, 2))
		redir->type = OUTPUT;
	if (!ft_strncmp(">>", (*tokens)->content, 3))
		redir->type = APPEND;
	*tokens = (*tokens)->next;
	redir->filename = ft_strdup((*tokens)->content);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	*tokens = (*tokens)->next;
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

t_list	*add_redir(t_list **tokens, t_list **redir)
{
	t_list	*new_node;
	t_redir	*new_redir;

	new_redir = construct_redir(tokens);
	if (!new_redir)
		return (NULL);
	new_node = ft_lstadd_backnew(redir, new_redir);
	if (!new_node)
		return (deconstruct_redir(&new_redir));
	*tokens = (*tokens)->next;
	return (new_node);
}
