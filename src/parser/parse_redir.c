/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parse_redir.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:14 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:14 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

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
	static const char	*names[] = {
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
		printf("\t\tRedir #%d: %s with type %s\n", i, redir->filename,
			get_redir_type_name(redir->type));
	}
}

void	get_next_redir(t_command *cmd, t_redir **redir)
{
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

t_redir	*construct_redir(t_list **tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = set_type((*tokens)->content, ft_strlen((*tokens)->content));
	*tokens = (*tokens)->next;
	redir->filename = ft_strdup((char *)(*tokens)->content);
	if (!redir->filename)
	{
		free(redir);
		redir = NULL;
	}
	return (redir);
}
