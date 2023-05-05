/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:07:21 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/04 19:07:23 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset(char **arguments, t_minishell *shell)
{
	size_t	i;

	i = 1;
	while (arguments[i])
		dict_remove_pair(&shell->env, arguments[i++]);
	return ;
}
