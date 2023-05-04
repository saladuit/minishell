/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   std_fds_close.c                                 |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:25 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:25 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	std_fds_close(int32_t *std_fds, t_status *status)
{
	if (close(std_fds[STDIN_FILENO]) != SUCCESS)
		*status = message_system_call_error("std_fds_close: ");
	if (close(std_fds[STDOUT_FILENO]) != SUCCESS)
		*status = message_system_call_error("std_fds_close: ");
}
