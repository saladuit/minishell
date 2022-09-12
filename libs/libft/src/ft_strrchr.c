/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 02:51:32 by saladin       #+#    #+#                 */
/*   Updated: 2021/07/26 15:55:33 by safoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;
	char		*curr;
	size_t		i;

	i = 0;
	p = s;
	curr = NULL;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (p[i])
	{
		if (p[i] == c)
			curr = (char *)p + i;
		i++;
	}
	return (curr);
}
