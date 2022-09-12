/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:50:33 by saladin       #+#    #+#                 */
/*   Updated: 2022/04/11 17:27:53 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"


static size_t	init_atoi(const char *nptr, int *sign)
{
	size_t	len;

	len = 0;
	while (ft_isspace((int)nptr[len]))
		len++;
	if (nptr[len] == '-')
	{
		*sign = -1;
		len++;
	}
	else if (nptr[len] == '+')
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	long long	nbr;
	size_t		i;
	int			sign;

	nbr = 0;
	sign = 1;
	i = init_atoi(nptr, &sign);
	while (nptr[i] && ft_isdigit((int)nptr[i]))
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	if (nbr * sign < -2147483648 || nbr * sign > 2147483647)
			return (0);
	return ((int)nbr * sign);
}
