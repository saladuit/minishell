/* ************************************************************************** */
/*                                                                            */
/*                                                                        0   */
/*   ft_lstiter.c                                    |o_o || |                */
/*                                                                        0   */
/*   By: safoh <safoh@student.codam.nl>                                   0   */
/*                                                                        0   */
/*   Created: 2022/02/09 20:56:55 by safoh                                0   */
/*   Updated: 2022/02/09 21:34:47 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int size;

	size = ft_lstsize(lst);
	while (size)
	{
		f(lst->content);
		lst = lst->next;
		size--;
	}
	return ;
}
