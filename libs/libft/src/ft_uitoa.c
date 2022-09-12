/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitoa.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/20 11:46:29 by safoh         #+#    #+#                 */
/*   Updated: 2021/09/22 13:59:53 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_uitoa(unsigned int nb)
{
	size_t		len;
	char		*result;
	size_t		neg;
	long long	buffer;

	buffer = nb;
	len = ft_numlen(buffer);
	neg = 0;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	if (buffer < 0)
	{
		buffer = -buffer;
		*result = '-';
		neg = 1;
	}
	while (len > neg)
	{
		len--;
		result[len] = (buffer % 10) + '0';
		buffer /= 10;
	}
	return (result);
}
