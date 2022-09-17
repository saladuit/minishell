/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser.h                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 16:03:42 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/17 15:40:50 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <ft_tree.h>
# include <libft.h>
# include <message.h>
# include <command.h>
# include <stdbool.h>

int32_t			parser(t_list **abstract_syntax_tree, t_list *command_line);
t_list			*get_abstract_syntax_tree(t_list *command_line);
t_command_table	*get_command_table(t_list **command_line);
t_command		*get_command(t_list **command_line);
char			*get_redirection(t_list **command_line);
char			*get_token(t_list **command_line);
#endif
