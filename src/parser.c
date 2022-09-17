#include <parser.h>
#include <stdio.h>

bool	ft_ismetachar(const char meta_c)
{
	if (meta_c == '>' || meta_c == '<' || meta_c == '|')
		return (true);
	return (false);
}
bool	ft_isdelimiter(const char sep)
{
	if (sep == '|')
		return (true);
	return (false);
}
t_command	*get_command(t_list **tokens)
{
	t_command	*command;
	char 		*token;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	while (*tokens)
	{
		token = (char *)(*tokens)->content;
		if (ft_isdelimiter(*token))
				break ;
		ft_lstadd_back(&command->tokens, ft_lstnew(*tokens));
		*tokens = (*tokens)->next;
	}
	return (command);
}

t_command_table	*get_command_table(t_list **tokens)
{
	t_command_table *command_table;
	t_list		*command;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
	{
		command = ft_lstnew((void *)get_command(tokens));
		if (!command)
			return (NULL);
		ft_lstadd_back(&command_table->commands, command);
	}
	return (command_table);
}

t_list		*get_abstract_syntax_tree(t_list *tokens)
{
	t_list	*abstract_syntax_tree;

	while (tokens)
	{
		abstract_syntax_tree = ft_lstnew((void *)get_command_table(&tokens));
		if (!abstract_syntax_tree)
			return (NULL);
		ft_lstadd_back(&abstract_syntax_tree, abstract_syntax_tree);
		if (!abstract_syntax_tree)
			return (NULL);
	}
	return (abstract_syntax_tree);
}

int32_t	parser(t_list **abstract_syntax_tree, t_list *tokens)
{
	*abstract_syntax_tree = get_abstract_syntax_tree(tokens);
	if (!*abstract_syntax_tree)
		return (ERROR);
	return (SUCCESS);
}
