/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_error_message.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:24:08 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:24:09 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_error_msg_not_valid(char *arg, t_status *status)
{
	ft_putstr_fd(SHELDON, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*status = E_GENERAL;
}
