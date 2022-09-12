/* ************************************************************************** */
/*                                                                            */
/*                                                                        0   */
/*   ft_lstclear.c                                   |o_o || |                */
/*                                                                        0   */
/*   By: safoh <safoh@student.codam.nl>                                   0   */
/*                                                                        0   */
/*   Created: 2022/02/09 17:21:13 by safoh                                0   */
/*   Updated: 2022/04/01 16:40:22 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	return ;
}
