#include <minishell.h>

static void	export_clear(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

int	ft_export(char **arguments, t_minishell *shell)
{
	char *key;
	char *value;
	int i;

	i = 0;
	if (arguments[i++] == NULL) 
	{
		dict_print(&shell->envd);
		return (SUCCESS);
	}
	while (arguments[i] != NULL)
	{
		key = ft_strdup(arguments[i]);
		if (key == NULL)
		{
			ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
			shell->exit_code = E_BUILTIN;
			i++;
			break ;
		}
		value = ft_strchr(key, '=');
		if (value == NULL) 
			value = ft_strdup("");
		else 
		{
			*value = '\0';
			value = ft_strdup(++value);
		}
		if (!value || dict_set(&shell->envd, key, value) == ERROR)
		{
			ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
			export_clear(key, value);
			shell->exit_code = E_BUILTIN;
			i++;
			break ;
		}
		i++;
	}
	return (SUCCESS);
}
