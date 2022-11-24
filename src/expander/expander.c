#include <message.h>
#include <expander.h>
#include <minishell.h>

char	*get_env_var(char **env, char *var_name)
{
	int32_t	i;
	int32_t	len;
	char	*str;

	i = 0;
	str = NULL;
	len = 0;
	while (var_name[len] && ft_isalpha(var_name[len]))
		len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len + 1] == '=')
		{
			str = ft_strdup(&env[i][len + 1]);
			if (!str)
				return (EMALLOC);
		}
		i++;
	}
	return (str);
}

int32_t	expand(t_list *token, t_minishell *shell)
{
	int32_t	i;
	int32_t	start;
	char	*to_expand;
	char	*expanded;
	char	*tmp;

	start = 0;
	to_expand = (char *)token->content;
	expanded = "";
	while (to_expand[i])
	{
		while (to_expand[i] && to_expand[i] != '$')
			i++;
		tmp = ft_substr(to_expand, start, i);
		expanded = ft_strjoin_free(expanded, tmp);
		free(tmp);
		tmp = get_env_var(shell->env, to_expand)
	}
	return (0);
}

int32_t	check_expand(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

/*
The expander needs to expand $variable name and $? depending on the quoting, remove outer quotes.


*/
int32_t	expander(t_minishell *shell)
{
	t_list	*tokens;

	tokens = shell->tokens;
	while (tokens)
	{
		if (check_expand((char *)tokens->content))
			expand(tokens, shell);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
