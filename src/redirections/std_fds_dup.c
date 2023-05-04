/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   std_fds_dup.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:29 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:29 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void std_fds_dup(int32_t *std_fds)
{
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
}
