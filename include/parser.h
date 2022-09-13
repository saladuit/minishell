/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser.h                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 16:03:42 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 17:07:11 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <ft_tree.h>
# include <libft.h>

int32_t	parser(t_list *tokens, t_tree **command_table);

#endif
