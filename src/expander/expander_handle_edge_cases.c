/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_dollar_and_alpha_or_underscore.c                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 09:53:15 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/17 09:53:17 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	handle_edge_cases(char *str)
{
	if (str[0] == '$')
	{
		if (ft_isalnum(str[1]) || str[1] == UNDERSCORE
			|| str[1] == '*' || str[1] == '#'
			|| str[1] == '-' || str[1] == '@'
			|| str[1] == '?' || str[1] == '$')
			return (true);
	}
	return (false);
}
