/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtolower.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/26 17:52:59 by safoh         #+#    #+#                 */
/*   Updated: 2021/08/26 17:53:18 by safoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_strtolower(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		string[i] = ft_tolower(string[i]);
		i++;
	}
	return ;
}
