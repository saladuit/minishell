/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   skip_whitespaces.c                              |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:45 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:45 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input))
		(*input)++;
}
