#include <minishell.h>

// str should start at a single quote. finds the next single quote and returns the lenght between the two.
int32_t	skip_single_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i + 1);
	}
	return (i);
}

// str should start at a double quote. finds the next double quote and returns the lenght between the two.
int32_t	skip_double_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\"')
			return (i + 1);
	}
	return (0);
}

// Skip the variables name. returns the length of the variable name that the string starts with.
int32_t	skip_variable_name(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (valid_varchar(str[i]))
		i++;
	return (i);
}

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

// get the correct environment variable for a given "var_name" string.
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

// loop through the string and expand all variables unless they are within single quotes.
char	*expand_variables(char *str, t_minishell *shell)
{
	int32_t	i;
	int32_t	start;
	char	*tmp;
	char	*new_str;

	i = 0;
	start = 0;
	new_str = calloc(1, 1);
	while (str[i])
	{
		while (str[i] != '$' && str[i] != '~' && str[i] != '\'' && str[i])
			i++;
		if (str[i] == '\'')
			i += skip_single_quotes(&str[i]);
		if (!str[i])
			break ;
		tmp = ft_substr(str, start, i - start);
		new_str = ft_strjoin_free_free(new_str, tmp);
		tmp = get_env_var(&str[i], shell);
		new_str = ft_strjoin_free_free(new_str, tmp);
		i += skip_variable_name(&str[i]);
		start = i;
	}
	return (ft_strjoin_free(new_str, &str[start]));
}

int32_t	skip_whitespace(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (i);
}

// counts the amount of splits needed for the str. counting quoted areas as a single word.
static int32_t	split_count(char *str)
{
	int32_t	i;

	i = 0;
	while (*str)
	{
		str += skip_whitespace(str);
		if (*str)
			i++;
		while (!ft_iswhitespace(*str) && *str)
		{
			if (*str == '\"')
				str += skip_double_quotes(str);
			else if (*str == '\'')
				str += skip_single_quotes(str);
			else
				str++;
		}
	}
	return (i);
}

// Finds the length and size of a word in regards to quotes and returns a newly allocated string using ft_substring.
static char	*get_word(char *str)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (!ft_iswhitespace(str[word_len]) && str[word_len])
	{
		if (str[word_len] == '\"')
			word_len += skip_double_quotes(&str[word_len]);
		else if (str[word_len] == '\'')
			word_len += skip_single_quotes(&str[word_len]);
		else
			word_len++;
	}
	word = ft_substr(str, 0, word_len);
	if (!word)
		return (NULL);
	return (word);
}

// Split words / sections based on whitespace. quoted words / sections do not get split.
char	**split_words(char *str)
{
	int32_t	i;
	int32_t	j;
	int32_t	count;
	char	**split;

	i = 0;
	j = 0;
	count = split_count(str);
	split = malloc((count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (str[i])
	{
		i += skip_whitespace(&str[i]);
		if (str[i])
		{
			split[j] = get_word(&str[i]);
			i += ft_strlen(split[j]);
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

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
	}
	return (ft_strjoin_free(trimmed, &str[start]));
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

// checks if a string needs expanding.
bool	needs_expanding(char *str)
{
	return (is_double_quoted(str)
		|| is_single_quoted(str)
		|| check_expand(str));
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

// Get the arguments and redirects out of the command structure so it can expand them if needed.
void	expand_cmd(t_command *cmd, t_minishell *shell)
{
	t_list	**arg_list;

	arg_list = &cmd->arguments;
	expand_argument_list(arg_list, shell);
	// expand_redirect_list(cmd->redirs, shell);
}

// loop over the command structures inside command table structure and start expanding for each.
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
