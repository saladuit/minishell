/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_validate.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:24:19 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:24:20 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	validate_alpha(char *arg, size_t *i, t_status *status)
{
	if (!ft_isalpha(arg[0]))
	{
		export_error_msg_not_valid(arg, status);
		(*i)++;
		return (false);
	}
	return (true);
}

void	validate_arg(char *arg, bool *ret)
{
	if (!arg)
		*ret = true;
}

bool	validate_dict(t_minishell *shell, char *key, size_t *i, bool *ret)
{
	if (dict_get(&shell->env, key) == NULL)
	{
		export_error_msg_out_of_memory(shell, i, ret);
		return (false);
	}
	return (true);
}
