#include <parser.h>


void	clean_abstract_syntax_tree(t_list **abstract_syntax_tree)
{
	t_command_table	*command_table;

	command_table = (*abstract_syntax_tree)->content;
	ft_lstclear(&command_table->commands, clean_command);
	ft_lstclear(abstract_syntax_tree, free);
}

t_list	*construct_abstract_syntax_tree(t_list *tokens)
{
	t_list	*abstract_syntax_tree;

	abstract_syntax_tree = NULL;
	while (tokens)
		if (!ft_lstadd_backnew(&abstract_syntax_tree, \
					(void *)get_command_table(&tokens)))
		{
			ft_lstclear(&abstract_syntax_tree, free);
			return (NULL);
		}
	return (abstract_syntax_tree);
}

int32_t parser(t_list **abstract_syntax_tree, t_list *tokens)
{
	*abstract_syntax_tree = construct_abstract_syntax_tree(tokens);
	if (!*abstract_syntax_tree)
	{
		ft_lstclear(&tokens, free);
		return (ERROR);
	}
	return (SUCCESS);
}
