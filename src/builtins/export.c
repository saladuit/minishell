#include <minishell.h>

static void	export_error_msg(char *arg, bool *not_valid)
{
		ft_putstr_fd(SHELDON, STDERR_FILENO);
		ft_putstr_fd(": export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		*not_valid = true;
}

static void	export_clear(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

int	ft_export(char **arguments, t_minishell *shell)
{
	bool 	not_valid;
	char	*key;
	char	*value;
	int		i;


	i = 0;
	if (!arguments[i++] && !arguments[i])
	{
		dict_print(&shell->env);
		return (SUCCESS);
	}
	while (arguments[i] != NULL)
	{
		if (!ft_isalpha(arguments[i][0]))
		{
			export_error_msg(arguments[i++], &not_valid);
			continue;
		}
		key = ft_strdup(arguments[i]);
		if (key == NULL)
		{
			ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
			shell->status = E_BUILTIN;
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
		if (!value || dict_set(&shell->env, key, value) == ERROR)
		{
			ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
			export_clear(key, value);
			shell->status = E_BUILTIN;
			i++;
			break ;
		}
		i++;
	}
	if (not_valid)
	{
		shell->status = E_GENERAL;
		return (CONTINUE);
	}
	return (SUCCESS);
}
