#include <minishell.h>

void	skip_until_quote_or_dollar(char *arg, size_t *i)
{
	while (arg[*i] && !is_dollar(arg[*i]) && !is_quote(arg[*i]))
		(*i)++;
}

char	*combine_expanded_strings(t_list *stack)
{
	char	*result;
	char	*tmp;

	tmp = NULL;
	result = ft_calloc(1, 1);
	while (stack)
	{
		tmp = ft_strjoin(result, stack->content);
		free(result);
		result = tmp;
		stack = stack->next;
	}
	return (result);
}

t_list	*copy_until_quote_or_dollar(char *arg, size_t *i)
{
	char	*expansion;
	t_list	*node;

	skip_until_quote_or_dollar(arg, i);
	expansion = ft_substr(arg, 0, *i);
	if (!expansion)
		return (NULL);
	node = ft_lstnew(expansion);
	return (node);
}

// Return the error code or the environment variable
// getenv
char	*expand_dollar(char *arg, t_exitstatus *status, t_dictionary *envd)
{
	char	*expansion;
	char	*sub;
	char	*p;

	if (*(++arg) == '\0')
		return (ft_strdup("$"));
	if (*arg == '?')
		return (ft_itoa(*status));
	p = ft_strchr(arg, '$');
	if (p)
	{
		sub = ft_substr(arg, 0, p - arg);
		expansion = dict_get(envd, sub);
		free(sub);
	}
	else
		expansion = dict_get(envd, arg);
	if (expansion == NULL)
		return (ft_strdup(""));
	return (ft_strdup(expansion));
}

char	*expand_token(char *arg, t_exitstatus *status, t_dictionary *envd);

t_list	*expand_double_quote_node(char *arg, size_t *i, t_exitstatus *status, t_dictionary *envd)
{
	t_list	*node;
	char	*expansion;
	char	*buf;

	if (*i >= 1)
		return (NULL);
	(*i)++;
	buf = ft_strchr(arg + 1, '\"');
	*buf = '\0';
	(*i) = buf - arg + 1;
	expansion = expand_token(arg + 1, status, envd);
	if (!expansion)
		return (NULL);
	node = ft_lstnew(expansion);
	return (node);
}

t_list	*expand_single_quote_node(char *arg, size_t *i)
{
	t_list	*node;
	char	*expansion;
	size_t	len;

	len = ft_strlen(arg) - 2;
	expansion = ft_substr(arg, 1, len);
	if (!expansion)
		return (NULL);
	(*i) += len + 2;
	node = ft_lstnew(expansion);
	return (node);
}

t_list	*expand_dollar_node(char *arg, size_t *i, t_exitstatus *status, t_dictionary *envd)
{
	t_list	*node;
	char	*expansion;

	expansion = expand_dollar(arg, status, envd);
	if (!expansion)
		return (NULL);
	(*i)++;
	skip_until_quote_or_dollar(arg, i);
	node = ft_lstnew(expansion);
	return (node);
}

char	*expand_token(char *arg, t_exitstatus *status, t_dictionary *envd)
{
	t_list	*stack;
	t_list	*node;
	char	*new_arg;
	size_t	i;

	i = 0;
	stack = NULL;
	node = NULL;
	while (arg[i])
	{
		if (is_dollar(arg[i]))
			node = expand_dollar_node(arg, &i, status, envd);
		else if (is_single_quote(arg[i]))
			node = expand_single_quote_node(arg, &i);
		else if (is_double_quote(arg[i]))
			node = expand_double_quote_node(arg, &i, status, envd);
		else
			node = copy_until_quote_or_dollar(arg, &i);
		if (node == NULL)
		{
			ft_lstclear(&stack, free);
			return (NULL);
		}
		ft_lstadd_back(&stack, node);
	}
	new_arg = combine_expanded_strings(stack);
	ft_lstclear(&stack, free);
	return (new_arg);
}
