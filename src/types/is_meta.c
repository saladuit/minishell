/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   is_meta.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:37:22 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:37:22 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_meta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_metas(const char *str)
{
	int	a;

	if (is_meta(str[0]))
	{
		a = str[0];
		if (str[1] == a)
			return (true);
	}
	return (false);
}
