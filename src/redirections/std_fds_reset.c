/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   std_fds_reset.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:35 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:35 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	std_fds_reset(int32_t *std_fds, t_status *status)
{
	if (dup2(std_fds[STDIN_FILENO], STDIN_FILENO) == ERROR)
		*status = message_system_call_error("std_fds_reset: ");
	if (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == ERROR)
		*status = message_system_call_error("std_fds_reset: ");
}
