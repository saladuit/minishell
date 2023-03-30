/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_print.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 14:07:58 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/03/30 14:08:00 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_print(char **list)
{
	int	i;

	if (!list || list[0] == NULL)
		return ;
	i = 0;
	while (list[i])
		ft_printf("%s\n", list[i++]);
}
