/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strbapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:04:56 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/09 10:04:57 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strbapi(char const *s, bool (*f)(int))
{
	size_t	i;
	size_t	len;

	if ((s == 0) || (f == 0))
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}
