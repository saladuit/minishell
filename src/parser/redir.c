#include <minishell.h>

void	deconstruct_redirs(void *redir)
{
	t_redir	*rdr;

	if (!redir)
		return ;
	rdr = (t_redir *)redir;
	free(rdr->filename);
	free(rdr);
}

static const char	*get_redir_type_name(t_type type)
{
	static const char *names[] = {
		[INPUT] = "INPUT",
		[OUTPUT] = "OUTPUT",
		[APPEND] = "APPEND",
		[HEREDOC] = "HEREDOC",
	};
	return (names[type]);
}

void	print_redirs(t_command *cmd)
{
	t_redir	*redir;
	int32_t	i;

	i = 0;
	while (i < cmd->n_redirs)
	{
		get_next_redir(cmd, &redir);
		i++;
		printf("\t\tRedir #%d: %s with type %s\n",
				i,
				redir->filename,
				get_redir_type_name(redir->type));
	}
}

void	get_next_redir(t_command *cmd, t_redir **redir)
{
	if (!cmd->redirs)
		return ;
	*redir = cmd->redirs->content;
	if (cmd->redirs->next == NULL)
	{
		cmd->redirs = cmd->redirs_head;
		return ;
	}
	else
		cmd->redirs = cmd->redirs->next;
	return ;
}

static t_type	set_type(char *symbol, size_t len)
{
	if (!ft_strncmp("<", symbol, len))
		return (INPUT);
	else if (!ft_strncmp("<<", symbol, len))
		return (HEREDOC);
	else if (!ft_strncmp(">", symbol, len))
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
	redir->filename = ft_strdup((char *)(*tokens)->content);
	return (redir);
}
