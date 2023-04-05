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

	if (!str || !str[0])
		return (0);
	len = 1;
	while (str[len] && !is_dollar(str[len]) && !is_quote(str[len]))
		len++;
	return (len);
}

static char	*edge_case_handling(char c, size_t *i, t_status *status)
{
	if ((c == '\0' || ft_iswhitespace(c)) && !is_dollar(c))
		return (ft_strdup("$"));
	if (c == '?')
		return (++(*i), ft_itoa(*status));
	if (c == '$' || ('0' < c && c <= '9') || c == '*' || c == '#' || c == '-'
		|| c == '_')
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

	expansion = edge_case_handling(arg[++(*i)], i, status);
	if (expansion)
		return (expansion);
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