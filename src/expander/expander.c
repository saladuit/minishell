/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 15:36:52 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/04/02 15:36:53 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

static size_t	len_until_quote_or_dollar(char *str)
{
	size_t	len;

	if (!str || !str[0])
		return (0);
	len = 1;
	while (str[len] && !is_dollar(str[len]) && !is_quote(str[len]))
		len++;
	return (len);
}

// getenv
char	*expand_dollar(char *arg, t_status *status, t_dictionary *env)
{
	char	*expansion;
	char	*sub;
	char	*p;
	size_t	len;

	if (*(arg + 1) == '\0')
		return (ft_strdup("$"));
	if (*(arg + 1) == '?')
		return (ft_itoa(*status));
	p = ft_strchr(arg, '$');
	len = len_until_quote_or_dollar(p);
	if (p)
	{
		if (len == 1)
			sub = ft_substr(p, 0, len);
		else
			sub = ft_substr(p, 1, len - 1);
		expansion = dict_get(env, sub);
		free(sub);
	}
	else
		expansion = dict_get(env, arg);
	if (expansion == NULL)
		return (ft_strdup(""));
	return (ft_strdup(expansion));
}

char	*expand_token(char *arg, t_status *status, t_dictionary *env);

t_list	*expand_double_quote_node(char *arg, size_t *i, t_status *status, t_dictionary *env)
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
	expansion = expand_token(arg + 1, status, env);
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

	len = ft_strlen(&arg[*i]) - 2;
	expansion = ft_substr(&arg[*i], 1, len);
	if (!expansion)
		return (NULL);
	(*i) += len + 2;
	node = ft_lstnew(expansion);
	return (node);
}

t_list	*expand_dollar_node(char *arg, size_t *i, t_status *status, t_dictionary *env)
{
	t_list	*node;
	char	*expansion;

	expansion = expand_dollar(&arg[*i], status, env);
	if (!expansion)
		return (NULL);
	*i += 2;
	skip_until_quote_or_dollar(arg, i);
	node = ft_lstnew(expansion);
	return (node);
}

//static int	is_two_quotes(char *arg)
//{
//	printf("%s\n", arg);
//	if ((is_single_quote(arg[0]) && is_single_quote(arg[1]))
//		|| (is_double_quote(arg[0]) && is_double_quote(arg[1])))
//		return (1);
//	return (0);
//}

char	*expand_token(char *arg, t_status *status, t_dictionary *env)
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
			node = expand_dollar_node(arg, &i, status, env);
		else if (is_double_quote(arg[i]) && is_dollar(arg[i + 1]))
			node = expand_double_quote_node(arg, &i, status, env);
		else if (is_single_quote(arg[i]) || is_double_quote(arg[i]))
			node = expand_single_quote_node(arg, &i);
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
