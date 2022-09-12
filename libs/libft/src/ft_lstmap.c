/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_lstmap.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: marvin <marvin@42.fr>                      //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/02/10 15:44:25 by marvin       /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/02/11 20:46:00 by marvin       \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void 	recursion(t_list *lst, void *(*f)(void *), t_list *new)
{
	if (lst == NULL)
		return ;
	ft_lstadd_back(&new, ft_lstnew(f(lst->content)));
	lst = lst->next;
	recursion(lst, f, new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	
	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	lst = lst->next;
	recursion(lst, f, new);
	if (del)
		ft_lstiter(lst, del);
	return (new);
}
