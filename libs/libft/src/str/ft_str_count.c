/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 13:25:39 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/12 13:25:40 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_str_count(char **args)
{
	size_t	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
