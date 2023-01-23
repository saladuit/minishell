#include <minishell.h>

// Get special variable values.
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
		return (ft_itoa(g_exitcode));
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
		i = find_var_start(str, i);
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
