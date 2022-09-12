/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_memalloc.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/10/01 17:12:00 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2021/10/01 17:16:47 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
