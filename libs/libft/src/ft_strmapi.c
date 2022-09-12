/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 02:51:25 by saladin       #+#    #+#                 */
/*   Updated: 2021/10/01 17:15:39 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*dest;
	size_t		len;

	if ((s == 0) || (f == 0))
		return (0);
	len = ft_strlen(s);
	dest = ft_strnew(len);
	if (!dest)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dest[len] = f(len, s[len]);
		len++;
	}
	return (dest);
}
