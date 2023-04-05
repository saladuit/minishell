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
	size_t	len;

	len = len_until_quote_or_dollar(&arg[*i]);
	expansion = ft_substr(&arg[*i], 0, len);
	if (!expansion)
		return (NULL);
	*i += len;
	node = ft_lstnew(expansion);
	return (node);
}

char	*expand_dollar(char *arg, size_t *i, t_status *status, t_dictionary *env)
{
	char	*expansion;
	char	*sub;
	size_t	len;

	if ((arg[++(*i)] == '\0' || ft_iswhitespace(arg[*i]))
		&& !is_dollar(arg[*i]))
		return (ft_strdup("$"));
	if (arg[*i] == '?')
		return (++(*i), ft_itoa(*status));
	if (arg[*i] == '$')
		return (++(*i), ft_strdup(""));
	len = *i;
	while (arg[++len] && !is_dollar(arg[len]) && !is_quote(arg[len])
		&& !ft_iswhitespace(arg[len]))
		;
	len -= *i;
	sub = ft_substr(&arg[*i], 0, len);
	expansion = dict_get(env, sub);
	free(sub);
	*i += len;
	if (expansion == NULL)
		return (ft_strdup(""));
	return (ft_strdup(expansion));
}

//char	*expand_token(char *arg, t_status *status, t_dictionary *env);

t_list	*expand_dollar_node(char *arg, size_t *i, t_status *status,
	t_dictionary *env)
{
	t_list	*node;
	char	*expansion;

	expansion = expand_dollar(arg, i, status, env);
	if (!expansion)
		return (NULL);
	node = ft_lstnew(expansion);
	return (node);
}

static void init_expander(size_t *i, t_dictionary *env)
{
	env->is_single = false;
	env->is_double = false;
	*i = 0;
}

#include <assert.h>
char	*expand_token(char *arg, t_status *status, t_dictionary *env)
{
	t_list	*stack;
	t_list	*node;
	char	*new_arg;
	size_t	i;

	stack = NULL;
	node = NULL;
	assert(arg);
	init_expander(&i, env);
	while (arg[i])
	{
		if (is_dollar(arg[i]) && !env->is_single)
			node = expand_dollar_node(arg, &i, status, env);
		else if (is_double_quote(arg[i]) && !env->is_single)
		{
			env->is_double ^= 1, i++;
			continue;
		}
		else if (is_single_quote(arg[i]) && !env->is_double)
		{
			env->is_single ^= 1, i++;
			continue;
		}
		else
			node = copy_until_quote_or_dollar(arg, &i);
		if (node == NULL)
			return (ft_lstclear(&stack, free), NULL);
		ft_lstadd_back(&stack, node);
	}
	new_arg = combine_expanded_strings(stack);
	ft_lstclear(&stack, free);
	return (new_arg);
}
