/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ultoh.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/26 17:58:42 by safoh         #+#    #+#                 */
/*   Updated: 2021/09/22 14:00:15 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	hexlen(unsigned long n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char	*ft_ultoh(unsigned long n)
{
	const char	hex[17] = "0123456789abcdef";
	char	*result;
	size_t	len;
	size_t	i;

	len = hexlen(n);
	i = 0;
	result = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		result[len - 1] = hex[n % 16];
		n /= 16;
		len--;
	}
	return (result);
}
