#include <command.h>
#include <libft.h>
#include <message.h>

t_command	*deconstruct_command(t_command **command)
{
	char	*filename;
	t_redir	*redir;

	if ((*command)->redir)
	{
		redir = (*command)->redir->content;
		filename = redir->filename;
		free(filename);
		free(redir);
	}
	ft_matrixfree(&(*command)->arguments);
	ft_lstclear(&(*command)->redir, free);
	free(*command);
	*command = NULL;
	return (NULL);
}

void	clean_command(void *ptr)
{
	t_command	*command;

	command = ptr;
	deconstruct_command(&command);
}

void	clean_abstract_syntax_tree(t_list **abstract_syntax_tree)
{
	t_command_table	*command_table;

	command_table = (*abstract_syntax_tree)->content;
	ft_lstclear(&command_table->commands, clean_command);
	ft_lstclear(abstract_syntax_tree, free);
}
