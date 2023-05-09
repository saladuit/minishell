/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrixclear.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:03:57 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/09 10:03:58 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_matrixfree(char ***string)
{
	size_t	i;

	i = 0;
	if (!*string)
		return ;
	while ((*string)[i])
	{
		free((*string)[i]);
		i++;
	}
	free(*string);
	*string = NULL;
}
