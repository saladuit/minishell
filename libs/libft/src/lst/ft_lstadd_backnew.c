#include <libft.h>

t_list	*ft_lstadd_backnew(t_list **lst, void *content)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(lst, new_node);
	return (new_node);
}
