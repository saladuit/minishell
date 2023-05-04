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

void	std_fds_dup(int32_t *std_fds, t_status *status)
{
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	if (std_fds[STDIN_FILENO] == ERROR)
		*status = message_system_call_error("std_fds_dup: ");
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (std_fds[STDOUT_FILENO] == ERROR)
		*status = message_system_call_error("std_fds_dup: ");
}
