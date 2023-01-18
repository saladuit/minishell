#include <minishell.h>

// Removes all unnecesarry quotes from strings.
char	*trim_quotes(char *str)
{
	int32_t	i;
	int32_t	start;
	char	*tmp;
	char	*trimmed;

	i = 0;
	start = 0;
	trimmed = calloc(1, 1);
	while (str[i])
	{
		while (str[i] != '\"' && str[i] != '\'' && str[i])
			i++;
		if (!str[i])
			break ;
		tmp = ft_substr(str, start, i - start);
		trimmed = ft_strjoin_free_free(trimmed, tmp);
		start = i + 1;
		if (str[i] == '\'')
			i += skip_single_quotes(&str[i]) - 1;
		else if (str[i] == '\"')
			i += skip_double_quotes(&str[i]) - 1;
		tmp = ft_substr(str, start, i - start);
		trimmed = ft_strjoin_free_free(trimmed, tmp);
		i++;
		start = i;
		trimmed = ft_strjoin_free(trimmed, &str[start]);
		free(str);
	}
	return (trimmed);
}

/*
Does all the steps needed to expand a string.
Expand all variables except ones in single quotes.
Then split the words if needed.
Then loop through the split words and remove quotes where needed.
*/
char	**expand_str(char *str, t_minishell *shell)
{
	char	**expanded_strings;
	char	*first_expand;
	int32_t	j;

	j = 0;
	first_expand = expand_variables(str, shell);
	expanded_strings = split_words(first_expand);
	while (expanded_strings[j])
	{
		expanded_strings[j] = trim_quotes(expanded_strings[j]);
		j++;
	}
	return (expanded_strings);
}

/* Expands arguments in the list and does word splitting if needed.
takes arg_node, content and shell.
if arg nodes content needs splitting adds nodes behind arg node.
*/
int32_t	expand_argument(t_list *arg_node, char *content, t_minishell *shell)
{
	t_list	*next;
	char	**expanded_content;
	int32_t	i;

	i = 0;
	expanded_content = expand_str(content, shell);
	if (!expanded_content || !expanded_content[i])
	{
		arg_node->content = (void *)expanded_content;
		return (i);
	}
	arg_node->content = (void *)expanded_content[i];
	next = arg_node->next;
	i++;
	while (expanded_content[i])
	{
		arg_node->next = ft_lstnew(expanded_content[i]);
		arg_node = arg_node->next;
		i++;
	}
	arg_node->next = next;
	return (i);
}

/*
Loops through the arguments and expands nodes that need expanding.
if expanded nodes return empty, "pop" that node from the list.
*/
void	expand_argument_list(t_list **arg_list, t_minishell *shell)
{
	int32_t	added_nodes;
	t_list	*node;

	added_nodes = 0;
	node = *arg_list;
	while (node)
	{
		if (needs_expanding((char *)node->content))
		{
			added_nodes = expand_argument(node, (char *)node->content, shell);
			if (added_nodes == 0)
				node = pop_node(arg_list, node);
		}
		if (added_nodes)
		{
			while (added_nodes && node)
			{
				node = node->next;
				added_nodes--;
			}
		}
		else if (node)
			node = node->next;
	}
}
