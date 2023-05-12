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

static char	*combine_expanded_strings(t_list *stack)
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

static t_list	*copy_until_quote_or_dollar(char *arg, size_t *i)
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
	if (!node)
	{
		free(expansion);
		return (NULL);
	}
	return (node);
}

static void	init_expander(t_expander *exp)
{
	exp->stack = NULL;
	exp->node = NULL;
	exp->is_single = false;
	exp->is_double = false;
	exp->i = 0;
}

static void	xor(t_expander *exp, bool single)
{
	if (single)
		exp->is_single ^= 1;
	else
		exp->is_double ^= 1;
	exp->i++;
	exp->e_continue = true;
}

char	*expand_token(char *arg, t_status *status, t_dictionary *env)
{
	t_expander	exp;

	init_expander(&exp);
	while (arg[exp.i])
	{
		exp.e_continue = false;
		if (ft_strncmp(arg, "$=", 2) && is_dollar(arg[exp.i]) && !exp.is_single)
			exp.node = expand_dollar_node(arg, &exp.i, status, env);
		else if (is_double_quote(arg[exp.i]) && !exp.is_single)
			xor(&exp, 0);
		else if (is_single_quote(arg[exp.i]) && !exp.is_double)
			xor(&exp, 1);
		else
			exp.node = copy_until_quote_or_dollar(arg, &exp.i);
		if (exp.e_continue)
			continue ;
		if (exp.node == NULL)
			return (ft_lstclear(&exp.stack, free), NULL);
		ft_lstadd_back(&exp.stack, exp.node);
	}
	exp.new_arg = combine_expanded_strings(exp.stack);
	ft_lstclear(&exp.stack, free);
	return (exp.new_arg);
}
