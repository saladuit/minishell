/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   is_whitespace.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/12 11:41:13 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/12 11:41:13 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_whitespace(int c)
{
	return (ft_iswhitespace(c));
}
