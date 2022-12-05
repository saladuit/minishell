#include <message.h>
#include <expander.h>
#include <minitype.h>
#include <minishell.h>
#include <ast.h>
#include <lexer.h>
#include <stdio.h>

// char	*get_env_var(char *var_name, t_minishell *shell)
// {
// 	int32_t	i;
// 	int32_t	len;
// 	char	*str;

// 	i = 0;
// 	len = 0;
// 	str = calloc(1, 1);
// 	while (var_name[len] && valid_varchar(var_name[len]))
// 		len++;
// 	if (!ft_strncmp(var_name, "?", len))
// 	{
// 		free(str);
// 		str = ft_itoa(shell->exit_code);
// 	}
// 	while (shell->env[i])
// 	{
// 		if (!ft_strncmp(shell->env[i], var_name, len)
// 			&& shell->env[i][len] == '=')
// 		{
// 			free(str);
// 			str = ft_strdup(&shell->env[i][len + 1]);
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// char	*expand_loop(char *content, char *expanded, t_minishell *shell)
// {
// 	int32_t	i;
// 	int32_t	start;
// 	char	*tmp;

// 	i = 0;
// 	while (content[i])
// 	{
// 		while (content[i] != '$' && content[i])
// 			i++;
// 		if (content[i] == '$')
// 		{
// 			tmp = ft_substr(content, start, i);
// 			if (!tmp)
// 				return (NULL);
// 			expanded = strjoin_free_free(expanded, tmp);
// 			tmp = get_env_var(&content[i + 1], shell);
// 			if (!tmp)
// 				return (NULL);
// 			expanded = strjoin_free_free(expanded, tmp);
// 			while (valid_varchar(content[i]))
// 				i++;
// 			start = i;
// 		}
// 	}
// 	return (ft_strjoin_free(expanded, &content[start]));
// }

// char	*expand(char *content, t_minishell *shell)
// {
// 	char	*expanded;

// 	if (!content)
// 		return (content);
// 	expanded = calloc(1, 1);
// 	if (expanded)
// 		expanded = expand_loop(content, expanded, shell);
// 	free(content);
// 	return (expanded);
// }

// char	*trim_quotes(char *str)
// {
// 	int32_t	len;
// 	char	*new_str;

// 	len = ft_strlen(str);
// 	new_str = malloc((len - 1) * sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	ft_strlcpy(new_str, str + 1, len - 1);
// 	free(str);
// 	return (new_str);
// }

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
// 	t_list	*tokens;
// 	t_list	*previous_token;
// 	char	*content;

// 	tokens = shell->tokens;
// 	while (tokens)
// 	{
// 		content = (char *)tokens->content;
// 		if (is_double_quoted(content) || is_single_quoted(content))
// 		{
// 			if (!is_single_quoted(content) && check_expand(content))
// 				content = expand(content, shell);
// 			content = trim_quotes(content);
// 		}
// 		else if (check_expand(content))
// 			content = expand(content, shell);
// 		if (!content)
// 			return (EMALLOC);
// 		if (!*content)
// 			pop_token(&tokens, previous_token, shell);
// 		else
// 		{
// 			tokens->content = (void *)content;
// 			previous_token = tokens;
// 			tokens = tokens->next;
// 		}
// 	}
// 	return (SUCCESS);
// }

void

void	expand_cmd(t_command *cmd)
{
	t_list	*arg_list;
	char	*content;

	content = (char *)arg_list->content;

}

void	expand_cmd_table(t_command_table *cmd_table)
{
	t_command	*cmd;
	t_list		*iter;

	iter = cmd_table->commands;
	while (iter)
	{
		cmd = (t_command *)iter->content;
		expand_cmd(cmd);
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
		expand_cmd_table(cmd_table);
		ast = ast->next;
	}
	return (SUCCESS);
}
