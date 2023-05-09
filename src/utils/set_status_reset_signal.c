/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_status_reset_signal.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:03:07 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/09 10:03:10 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_status_reset_signal(t_status *status)
{
	*status = E_GENERAL;
	g_signal_error = E_USAGE;
}
