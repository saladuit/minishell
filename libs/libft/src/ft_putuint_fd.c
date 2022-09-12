/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putuint_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/20 11:41:53 by safoh         #+#    #+#                 */
/*   Updated: 2021/08/20 11:43:45 by safoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putuint_fd(unsigned int nb, int fd)
{
	char	*result;

	result = ft_uitoa(nb);
	ft_putstr_fd(result, fd);
	free(result);
	return ;
}
