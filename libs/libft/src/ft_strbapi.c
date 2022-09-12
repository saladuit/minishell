/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strbapi.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 02:51:25 by saladin       #+#    #+#                 */
/*   Updated: 2022/03/31 18:52:55 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
		if(!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}
