/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ltoi_with_overflow.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:04:18 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/09 10:04:19 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include "libft.h"

static bool	iterate_and_create(const char *str, size_t i,
								size_t len, long *result)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i == len - 1 && str[i] != '0')
			*result = (*result * 10) - 1 + (str[i] - '0');
		else
			*result = *result * 10 + str[i] - '0';
		if (*result < 0 && *result != INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_ltoi_with_overflow(const char *str, long *result)
{
	size_t	i;
	long	sign;
	size_t	len;

	sign = 1;
	i = 0;
	*result = 0;
	if (!str)
		return (1);
	len = ft_strlen(str);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!iterate_and_create(str, i, len, result))
		return (false);
	*result *= sign;
	return (true);
}
