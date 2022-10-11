/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:03:42 by safoh         #+#    #+#                 */
/*   Updated: 2022/10/10 13:18:27 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <ft_tree.h>
# include <libft.h>
# include <message.h>
# include <command.h>
# include <stdbool.h>

int32_t			parser(t_list **abstract_syntax_tree, t_list *tokens);
t_list			*get_abstract_syntax_tree(t_list *tokens);
t_command_table	*get_command_table(t_list **tokens);
t_command		*get_command(t_list **tokens);
char			*get_redirection(t_list **tokens);
char			*get_token(t_list **tokens);
void			clean_abstract_syntax_tree(t_list **abstract_syntax_tree);
#endif
