#include <minishell.h>

static void	export_error_msg_not_valid(char *arg, t_status *status)
{
	ft_putstr_fd(SHELDON, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*status = E_GENERAL;
}

static void	export_error_msg_out_of_memory(t_minishell *shell, size_t *i)
{
	ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
	shell->status = E_GENERAL;
	(*i)++;
}

static void	get_value(char **value, char *key)
{
	*value = ft_strchr(key, '=');
	if (*value == NULL)
		*value = ft_strdup("");
	else
	{
		**value = '\0';
		*value = ft_strdup(++(*value));
	}
}

void	ft_export(char **arguments, t_minishell *shell)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 1;
	if (!arguments[i])
		return ;
	while (arguments[i] != NULL)
	{
		if (!ft_isalpha(arguments[i][0]))
		{
			export_error_msg_not_valid(arguments[i++], &shell->status);
			continue ;
		}
		key = ft_strdup(arguments[i]);
		if (key == NULL)
		{
			export_error_msg_out_of_memory(shell, &i);
			return ;
		}
		get_value(&value, key);
		if (!value)
		{
			export_error_msg_out_of_memory(shell, &i);
			return ;
		}
		dict_set(&shell->env, key, value);
		if (dict_get(&shell->env, key) == NULL)
		{
			export_error_msg_out_of_memory(shell, &i);
			return ;
		}
		i++;
	}
	return ;
}
