#include <minishell.h>

// checks if a string needs expanding.
bool	needs_expanding(char *str)
{
	return (is_double_quoted(str)
		|| is_single_quoted(str)
		|| check_expand(str));
}

bool	valid_varchar(char c)
{
	return (!ft_iswhitespace(c) && !is_quote(c) && c);
}

int32_t	check_expand(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free_free(char *expanded, char *tmp)
{
	expanded = ft_strjoin_free(expanded, tmp);
	free(tmp);
	return (expanded);
}

/**
 * @brief Pops a node from a list, frees content, the node itself
 * and returns the address to the next node in the list.
 *
 * @param list The list from which to pop the node.
 * @param node The node to be popped.
 * @return t_list * pointer to the next node from the one that was popped.
 *  NULL if it was the last node, 'pop_node' if the node was not in the list.
 */
t_list	*pop_node(t_list **list, t_list *pop_node)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *list;
	prev = tmp;
	while (tmp)
	{
		if (tmp == pop_node)
		{
			prev->next = tmp->next;
			if (tmp == *list)
				*list = tmp->next;
			tmp = tmp->next;
			free(pop_node->content);
			free(pop_node);
			return (tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (pop_node);
}
