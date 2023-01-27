#include <minishell.h>

void	expand_redirect_list(t_list **redirects, t_minishell *shell)
{
	t_redir	*redir;
	t_list	*node;
	char	*expanded_str;

	node = *redirects;
	printf("Before expansion: %s\n", ((t_redir *)node->content)->filename);
	while (node)
	{
		redir = node->content;
		if (needs_expanding(redir->filename))
		{
			expanded_str = expand_variables(redir->filename, shell);
			expanded_str = trim_quotes(expanded_str);
			redir->filename = expanded_str;
		}
		printf("Expander: %s\n", redir->filename);
		node = node->next;
	}
}
