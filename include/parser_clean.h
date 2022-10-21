#ifndef PARSER_CLEAN_H
# define PARSER_CLEAN_H

int32_t	ft_matrixclear(char ***string);
void	clean_command(void *ptr);
t_command	*deconstruct_command(t_command **command);
void			clean_abstract_syntax_tree(t_list **abstract_syntax_tree);

#endif
