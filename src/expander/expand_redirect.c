#include <minishell.h>

void	expand_redirect_list(t_list **redirects, t_minishell *shell)
{
	t_redir	*redir;
	t_list	*node;
	char	*expanded_str;

	node = *redirects;
	while (node)
	{
		redir = node->content;
		if (needs_expanding(redir->filename))
		{
			if (redir->type != HEREDOC)
				expanded_str = expand_variables(redir->filename, shell);
			expanded_str = trim_quotes(expanded_str);
			free(redir->filename);
			redir->filename = expanded_str;
		}
		if (redir->type == HEREDOC)
		{
			redir->filename = add_heredoc(redir->filename);
		}
		node = node->next;
	}
}
