#include <message.h>
#include <expander.h>
#include <minishell.h>

char	*get_env_var(char **env, char *var_name, t_minishell *shell)
{
	int32_t	i;
	int32_t	len;
	char	*str;

	i = 0;
	len = 0;
	str = calloc(1, 1);
	while (var_name[len] && !ft_iswhitespace(var_name[len]))
		len++;
	if (!ft_strncmp(var_name, "?", len))
	{
		free(str);
		str = ft_itoa(shell->exit_code);
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
		{
			free(str);
			str = ft_strdup(&env[i][len + 1]);
		}
		i++;
	}
	return (str);
}

char	*strjoin_free_free(char *expanded, char *tmp)
{
	expanded = ft_strjoin_free(expanded, tmp);
	free(tmp);
	return (expanded);
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
			tmp = get_env_var(shell->env, &content[i + 1], shell);
			if (!tmp)
				return (NULL);
			expanded = strjoin_free_free(expanded, tmp);
			while (!ft_iswhitespace(content[i]) && content[i])
				i++;
			start = i;
		}
	}
	return (ft_strjoin_free(expanded, &content[start]));
}

char	*expand(char *content, t_minishell *shell)
{
	char	*expanded;

	expanded = calloc(1, 1);
	expanded = expand_loop(content, expanded, shell);
	free(content);
	return (expanded);
}

int32_t	check_expand(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int32_t	is_double_quoted(char *str)
{
	if (*str == '\"')
	{
		if (str[ft_strlen(str) - 1] == '\"')
			return (1);
	}
	return (0);
}

int32_t	is_single_quoted(char *str)
{
	if (*str == '\'')
	{
		if (str[ft_strlen(str) - 1] == '\'')
			return (1);
	}
	return (0);
}

char	*quote_trim(char *str)
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

/* The expander needs to expand $variable name and $? depending on the quoting.
	remove outer quotes.


*/
int32_t	expander(t_minishell *shell)
{
	t_list	*tokens;
	char	*content;

	tokens = shell->tokens;
	while (tokens)
	{
		content = (char *)tokens->content;
		if (is_double_quoted(content))
		{
			content = quote_trim(content);
			if (!content)
				return (EMALLOC);
			if (check_expand(content))
				content = expand(content, shell);
		}
		else if (is_single_quoted(content))
		{
			content = quote_trim(content);
			if (!content)
				return (EMALLOC);
		}
		else if (check_expand(content))
			content = expand(content, shell);
		tokens->content = (void *)content;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
