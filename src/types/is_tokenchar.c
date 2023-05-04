/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   is_tokenchar.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:38:27 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:38:27 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_metachar(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2) || is_meta(*str))
		return (true);
	return (false);
}

size_t	metachar_len(const char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	else
		return (1);
}
