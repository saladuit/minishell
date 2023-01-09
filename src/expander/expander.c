#include <minishell.h>

char	*special_variable(char *var_name, t_minishell *shell)
{
	int32_t	i;

	i = 0;
	if (!ft_strncmp(var_name, "~", 1))
	{
		while (shell->env[i])
		{
			if (!ft_strncmp(shell->env[i], "HOME=", 5))
			{
				return (ft_strdup(&shell->env[i][5]));
			}
			i++;
		}
	}
	else if (!ft_strncmp(var_name, "?", 1))
		return (ft_itoa(shell->exit_code));
	if (ft_isdigit(var_name[i]))
	{
		i++;
		while (valid_varchar(var_name[i]))
			i++;
		return (ft_substr(var_name, 1, i - 1));
	}
	return (NULL);
}

char	*get_env_var(char *var_name, t_minishell *shell)
{
	int32_t	i;
	int32_t	len;
	char	*str;

	len = 0;
	if (*var_name == '$')
		var_name++;
	while (valid_varchar(var_name[len]))
		len++;
	if (!ft_strncmp(var_name, "?", len) || !ft_strncmp(var_name, "~", len)
		|| ft_isdigit(var_name[0]))
		return (special_variable(var_name, shell));
	i = 0;
	str = calloc(1, 1);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var_name, len)
			&& shell->env[i][len] == '=')
		{
			free(str);
			str = ft_strdup(&shell->env[i][len + 1]);
		}
		i++;
	}
	return (str);
}

char	*expand_loop(char *content, char *expanded, t_minishell *shell)
{
	int32_t	i;
	int32_t	start;
	char	*tmp;

	i = 0;
	start = 0;
	while (content[i])
	{
		while (content[i] != '$' && content[i] != '~' && content[i])
			i++;
		if (!content[i])
			break ;
		tmp = ft_substr(content, start, i - start);
		expanded = strjoin_free_free(expanded, tmp);
		tmp = get_env_var(&content[i], shell);
		expanded = strjoin_free_free(expanded, tmp);
		i++;
		while (valid_varchar(content[i]))
			i++;
		start = i;
	}
	return (ft_strjoin_free(expanded, &content[start]));
}

char	*expand(char *content, t_minishell *shell)
{
	char	*expanded;

	if (!content)
		return (content);
	expanded = calloc(1, 1);
	if (expanded)
		expanded = expand_loop(content, expanded, shell);
	free(content);
	return (expanded);
}

char	*make_trimmed_str()
{

}

char	*trim_quotes(char *str)
{
	int32_t	len;
	char	*new_str;
	int32_t	i;

	i = 0;
	while ((str[i] != '\"' || str[i] != '\'') && str[i])
		i++;

	len = ft_strlen(str);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str + 1, len - 1);
	free(str);
	return (new_str);
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

static int32_t	split_count(char *str)
{
	int32_t	i;

	i = 0;
	while (*str)
	{
		while (ft_iswhitespace(*str))
			str++;
		if (*str)
			i++;
		while (!ft_iswhitespace(*str) && *str)
			str++;
	}
	return (i);
}

static char	*get_word(const char *str)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (!ft_iswhitespace(str[word_len]) && str[word_len])
		word_len++;
	word = ft_substr(str, 0, word_len);
	if (!word)
		return (NULL);
	return (word);
}

bool	needs_expanding(char *str)
{
	return (is_double_quoted(str)
		|| is_single_quoted(str)
		|| check_expand(str));
}

char	**word_split(char **expanded_str, int32_t *j)
{
	int32_t	i;
	int32_t	j;
	int32_t	count;
	char	**split_words;

	i = 0;
	j = 0;
	count = split_count(str);
	split_words = malloc((count + 1) * sizeof(char *));
	if (!split_words)
		return (NULL);
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i])
		{
			split_words[j] = get_word(&str[i]);
			j++;
		}
		while (str[i] && !ft_iswhitespace(str[i]))
			i++;
	}
	split_words[j] = NULL;
	return (split_words);
}

char	**expand_single_quotes(
			char *str, char **expanded_str, int32_t *i, int32_t *j)
{
	int32_t	start;
	char	*trimmed_part;

	start = *i;
	while (str[*i] != '\'' && str[*i])
		*i++;
	if (str[*i] == '\'')
	{
		trimmed_part = ft_substr(str, start, (*i - start));
		expanded_str[*j] = strjoin_free_free(expanded_str[*j], trimmed_part);
	}
	return (expanded_str);
}

char	**expand_double_quotes(
			char *str, char **expanded_str, int32_t *i, int32_t *j)
{

	return (expanded_str);
}

char	**expand_variable(
			char *str, char **expanded_str, int32_t *i, int32_t *j)
{
	return (expanded_str);
}

char	**expand_str(char *str, t_minishell *shell)
{
	char	**expanded_str;
	int32_t	i;
	int32_t	j;
	int32_t	start;

	i = 0;
	j = 0;
	expanded_str = ft_calloc(1, sizeof(char *));
	while (str[i])
	{
		start = i;
		while ((str[i] != '\'' || str[i] != '\"' || str[i] != '$') && str[i])
			i++;
		expanded_str[j] = strjoin_free_free(expanded_str,
				ft_substr(str, start, i - start));
		if (str[i] == '\'')
			expanded_str = expand_single_quotes(str, expanded_str, &i, &j);
		else if (str[i] == '\"')
			expanded_str = expand_double_quotes(str, expanded_str, &i, &j);
		else if (str[i] == '$')
		{
			expanded_str = expand_variable(str, expanded_str, &i, &j);
			expanded_str = word_split(expanded_str, &j);
		}
		i++;
	}
	// if (is_double_quoted(str) || is_single_quoted(str))
	// {
		// if (!is_single_quoted(str) && check_expand(str))
		// 	str = expand(str, shell);
		// str = trim_quotes(str);
		// expanded_str = malloc(2 * sizeof(char *));
		// if (str && expanded_str)
		// {
		// 	expanded_str[0] = str;
		// 	expanded_str[1] = NULL;
		// }
	// }
	else if (check_expand(str))
	{
		str = expand(str, shell);
		if (str)
			expanded_str = word_split(str);
	}
	if (!str)
		return (NULL);
	return (expanded_str);
}

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

void	expand_cmd(t_command *cmd, t_minishell *shell)
{
	t_list	**arg_list;

	arg_list = &cmd->arguments;
	expand_argument_list(arg_list, shell);
	// expand_redirect_list(cmd->redirs, shell);
}

void	expand_cmd_table(t_command_table *cmd_table, t_minishell *shell)
{
	t_command	*cmd;
	t_list		*iter;

	iter = cmd_table->commands;
	while (iter)
	{
		cmd = (t_command *)iter->content;
		expand_cmd(cmd, shell);
		iter = iter->next;
	}
}

/* The expander needs to expand $variable name and $? depending on the quoting.
	check if it is quoted.
	then check if it is double quoted.
	if it is double quoted expand if needed.
	single quotes do not have to be expanded.
	remove quotes.

	No quotes? and it is a $variable?
	Expand it into multiple arguments
*/
int32_t	expander(t_minishell *shell)
{
	t_command_table	*cmd_table;
	t_list			*ast;

	ast = shell->ast;
	while (ast)
	{
		cmd_table = (t_command_table *)ast->content;
		expand_cmd_table(cmd_table, shell);
		ast = ast->next;
	}
	return (SUCCESS);
}
