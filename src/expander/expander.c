#include <minishell.h>

char	*get_env_var(char *var_name, t_minishell *shell)
{
	int32_t	i;
	int32_t	len;
	char	*str;

	i = 0;
	len = 0;
	str = calloc(1, 1);
	while (var_name[len] && valid_varchar(var_name[len]))
		len++;
	if (!ft_strncmp(var_name, "?", len))
	{
		free(str);
		str = ft_itoa(shell->exit_code);
	}
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
	while (content[i])
	{
		while (content[i] != '$' && content[i])
			i++;
		if (content[i] == '$')
		{
			tmp = ft_substr(content, start, i);
			if (!tmp)
				return (NULL);
			expanded = strjoin_free_free(expanded, tmp);
			tmp = get_env_var(&content[i + 1], shell);
			if (!tmp)
				return (NULL);
			expanded = strjoin_free_free(expanded, tmp);
			while (valid_varchar(content[i]))
				i++;
			start = i;
		}
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
	// free(content);
	return (expanded);
}

char	*trim_quotes(char *str)
{
	int32_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc((len - 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str + 1, len - 1);
	free(str);
	return (new_str);
}

// void	pop_token(t_list **token, t_list *prev_token, t_minishell *shell)
// {
// 	if (*token == shell->tokens)
// 	{
// 		shell->tokens = (*token)->next;
// 		prev_token = *token;
// 		*token = (*token)->next;
// 		free(prev_token);
// 		return ;
// 	}
// 	prev_token->next = (*token)->next;
// 	free(*token);
// 	*token = prev_token->next;
// }

// /* The expander needs to expand $variable name and $? depending on the quoting.
// 	remove outer quotes.


// */
// int32_t	expander(t_minishell *shell)
// {
// 	char	*content;

// 	if (is_double_quoted(content) || is_single_quoted(content))
// 	{
// 		if (!is_single_quoted(content) && check_expand(content))
// 			content = expand(content, shell);
// 		content = trim_quotes(content);
// 	}
// 	else if (check_expand(content))
// 		content = expand(content, shell);
// 	if (!content)
// 		return (EMALLOC);
// 	return (SUCCESS);
// }

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

// static char	*get_word(const char *str)
// {
// 	char	*word;
// 	size_t	word_len;

// 	word_len = 0;
// 	while (!ft_iswhitespace(str[word_len]))
// 		word_len++;
// 	word = ft_substr(str, 0, word_len);
// 	if (!word)
// 		return (NULL);
// 	return (word);
// }

char	**word_split(char *str)
{
	int32_t	i;
	int32_t	j;
	int32_t	count;
	char	**split_words;

	i = 0;
	j = 0;
	count = split_count(str);
	split_words = malloc((count + 1) * sizeof(char *));
	printf("%i\n", count);
	if (!split_words)
		return (NULL);
	while (str[i])
	{
		// while (ft_iswhitespace(str[i]))
		// {
		// 	printf("%i\n", i);
		// 	i++;
		// }
		// if (*str)
		// {
		// 	split_words[j] = get_word(&str[i]);
		// 	j++;
		// }
		// while (str[i] && !ft_iswhitespace(str[i]))
		// {
		// 	printf("%i\n", i);
		// 	i++;
		// }
		printf("Iterating...");
		i++;
	}
	split_words[j] = NULL;
	return (split_words);
}

char	**expand_str(char *str, t_minishell *shell)
{
	char	**expanded_str;

	expanded_str = NULL;
	printf("->%s<-\n\n", str);
	if (is_double_quoted(str) || is_single_quoted(str))
	{
		printf("Quoted\n");
		if (!is_single_quoted(str) && check_expand(str))
			str = expand(str, shell);
		str = trim_quotes(str);
		expanded_str = malloc(2 * sizeof(char *));
		if (str && expanded_str)
		{
			expanded_str[0] = str;
			expanded_str[1] = NULL;
		}
	}
	else if (check_expand(str))
	{
		printf("Not quoted\n");
		str = expand(str, shell);
		printf(">%s<\n", str);
		if (str)
			expanded_str = word_split(str);
	}
	if (!str)
		return (NULL);
	return (expanded_str);
}

int32_t	expand_argument(t_list **arg_node, char *content, t_minishell *shell)
{
	t_list	*next;
	char	**expanded_content;
	int32_t	i;

	i = 0;
	expanded_content = expand_str(content, shell);
	if (!expanded_content)
	{
		(*arg_node)->content = (void *)expanded_content;
		return (i);
	}
	(*arg_node)->content = (void *)expanded_content[i];
	next = (*arg_node)->next;
	i++;
	while (expanded_content[i])
	{
		(*arg_node)->next = ft_lstnew(expanded_content[i]);
		*arg_node = (*arg_node)->next;
	}
	(*arg_node)->next = next;
	return (i);
}

void	expand_argument_list(t_list *arg_list, t_minishell *shell)
{
	char	*content;
	int32_t	added_nodes;
	// t_list	*prev;
	// t_list	*tmp;

	added_nodes = 0;
	// prev = arg_list;
	while (arg_list)
	{
		content = (char *)arg_list->content;
		added_nodes = expand_argument(&arg_list, content, shell);
		// if (added_nodes == -1)
		// {
			// tmp = arg_list;
			// arg_list = arg_list->next;
			// prev->next = arg_list;
			// free(arg_list);
		// }
		while (added_nodes)
		{
			arg_list = arg_list->next;
			added_nodes--;
		}
		if (arg_list)
		{
			// prev = arg_list;
			arg_list = arg_list->next;
		}
	}
}

void	expand_cmd(t_command *cmd, t_minishell *shell)
{
	t_list	*arg_list;

	arg_list = cmd->arguments;
	expand_argument_list(arg_list, shell);
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
