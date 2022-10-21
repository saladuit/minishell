#ifndef PARSER_H
# define PARSER_H

# include <libft.h>
# include <command_table.h>
# include <command.h>
# include <message.h>

int32_t	parser(t_list **abstract_syntax_tree, t_list *tokens);
t_list	*get_abstract_syntax_tree(t_list *tokens);
void	clean_abstract_syntax_tree(t_list **abstract_syntax_tree);

#endif
