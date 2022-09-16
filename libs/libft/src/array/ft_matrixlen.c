/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrixlen.c                                  |o_o || |                */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 14:18:41 by dritsema      #+#    #+#                 */
/*   Updated: 2022/09/16 11:05:36 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_matrixlen(void **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
