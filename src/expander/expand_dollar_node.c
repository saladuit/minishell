/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar_node.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 14:27:02 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/04/05 14:27:06 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	len_until_quote_or_dollar(char *str)
{
	size_t	len;

	len = 1;
	while (str[len] && !is_dollar(str[len]) && !is_quote(str[len]))
		len++;
	return (len);
}

static char	*edge_case_handling(char c, size_t *i, t_status *status, char *arg)
{
	(void)arg;
	if (c == '\0' || ft_iswhitespace(c) || is_quote(c))
		return (ft_strdup("$"));
	if (c == '?')
		return (++(*i), ft_itoa(*status));
	if (c == '$' || ('0' < c && c <= '9') || c == '*' || c == '#' || c == '-')
		return (++(*i), ft_strdup(""));
	if (c == '0')
		return (++(*i), ft_strdup(SHELDON));
	return (NULL);
}

char	*expand_dollar(char *arg, size_t *i, t_status *status,
		t_dictionary *env)
{
	char	*expansion;
	char	*sub;
	size_t	len;

	expansion = edge_case_handling(arg[++(*i)], i, status, arg);
	if (expansion)
		return (expansion);
	len = *i;
	while (arg[len] && !is_dollar(arg[len]) && !is_quote(arg[len])
		&& !ft_iswhitespace(arg[len]) && !is_equalssign(arg[len]))
		len++;
	len -= *i;
	sub = ft_substr(&arg[*i], 0, len);
	if (sub == NULL)
		return (NULL);
	expansion = dict_get(env, sub);
	free(sub);
	*i += len;
	if (expansion == NULL)
		return (ft_strdup(""));
	return (ft_strdup(expansion));
}

t_list	*expand_dollar_node(char *arg, size_t *i, t_status *status,
		t_dictionary *env)
{
	t_list	*node;
	char	*expansion;

	expansion = expand_dollar(arg, i, status, env);
	if (!expansion)
		return (NULL);
	node = ft_lstnew(expansion);
	if (!node)
	{
		free(expansion);
		return (NULL);
	}
	return (node);
}
