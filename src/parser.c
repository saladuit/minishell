/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 17:09:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/17 11:56:41 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <message.h>


void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input) && **input)
		(*input)++;
}

t_command	*get_command(const char **command_line)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (**command_table)
	{
		ft_skip_whitespaces(command_line);
	}
}

t_command_table	*get_command_table(const char **command_line)
{
	t_command_table *command_table;
	t_command		command;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (**command_line)
	{
		ft_skip_whitespaces(command_line);
		command = ft_lstnew(get_command(command_line));
		if (!command)
			return (NULL);
		ft_lstadd_back(&command_table->commands, command);
	}
	return (command_table);
}

t_list		*get_abstract_syntax_tree(const char *command_line)
{
	t_list	*abstract_syntax_tree;

	while (*command_line)
	{
		ft_skip_whitespaces(&command_line);
		abstract_syntax_tree = ft_lstnew(get_command_table(&command_line));
		if (!abstract_syntax_tree)
			return (NULL);
		ft_lstadd_back(&abstract_syntax_tree, abstract_syntax_tree);
		if (!abstract_syntax_tree)
			return (NULL);
	}
	return (abstract_syntax_tree);
}

int32_t	parser(t_list **abstract_syntax_tree, const char *command_line)
{
	*abstract_syntax_tree = get_abstract_syntax_tree(command_line);
	if (!*abstract_syntax_tree)
		return (ERROR);
	return (SUCCESS);
}
