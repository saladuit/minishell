/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser.h                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 16:03:42 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/17 11:54:32 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <ft_tree.h>
# include <libft.h>

int32_t			parser(t_list **abstract_syntax_tree, const char *command_line);
t_list			*get_abstract_syntax_tree(const char *command_line);
t_command_table	*get_command_table(const char **command_line);
t_command		*get_command(const char **command_line);
char			*get_redirection(const char **command_line);
char			*get_token(const char **command_line);
#endif
