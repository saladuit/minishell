/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 15:36:21 by dritsema      #+#    #+#                 */
/*   Updated: 2022/06/08 12:51:47 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates sufficient memory for a copy of the string s1,
 * does the copy, and returns a pointer to it.
 * The pointer may subsequently be used as an argument to the function free().
 *
 * @param s1 The string to copy.
 * @return Pointer to the copied string.
 */
char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*temp;
	int		strsize;

	strsize = ft_strlen(s1);
	dup = malloc((strsize + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	temp = dup;
	while (*s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	dup[strsize] = '\0';
	return (dup);
}
