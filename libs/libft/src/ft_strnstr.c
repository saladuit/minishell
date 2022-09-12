/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 02:51:30 by saladin       #+#    #+#                 */
/*   Updated: 2021/10/14 14:10:24 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(little);
	if (*little == '\0' || little == NULL || len == 0 || little == big)
		return ((char *)big);
	while (i < len)
	{
		if (!ft_strncmp(big + i, little, j) && i + j < len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
