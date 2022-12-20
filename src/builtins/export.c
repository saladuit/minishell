#include <minishell.h>

char	**export_addvar(char **env, char *argument)
{
	int32_t	i;
	int32_t	new_size;
	char	**tmp;

	i = 0;
	new_size = ft_matrixlen((void **)env) + 2;
	tmp = calloc(new_size, sizeof(char *));
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = ft_strdup(argument);
	free(env);
	return (tmp);
}

void	export_replacevar(char **env, char *argument)
{
	int32_t	i;
	char	*var_name;

	i = 0;
	var_name = calloc(varname_len(argument) + 1, sizeof(char));
	if (var_name)
		ft_strlcpy(var_name, argument, varname_len(argument) + 1);
	while (env[i])
	{
		if (!ft_strncmp(var_name, env[i], ft_strlen(var_name)))
		{
			free(env[i]);
			env[i] = ft_strdup(argument);
		}
		i++;
	}
}

void	export_var(char **arguments, t_minishell *shell)
{
	int32_t	i;

	i = 1;
	while (arguments[i])
	{
		if (!valid_var(arguments[i]))
		{
			export_error(arguments[i]);
			i++;
			continue ;
		}
		if (in_env(arguments[i], shell->env) && has_equals(arguments[i]))
			export_replacevar(shell->env, arguments[i]);
		else if (has_equals(arguments[i]))
			shell->env = export_addvar(shell->env, arguments[i]);
		if (in_env(arguments[i], shell->expo))
			export_replacevar(shell->expo, arguments[i]);
		else
			shell->expo = export_addvar(shell->expo, arguments[i]);
		sort_export(shell->expo);
		i++;
	}
}

int	ft_export(char **arguments, t_minishell *shell)
{
	if (ft_matrixlen((void **)arguments) > 1)
		export_var(arguments, shell);
	else
		print_expo(shell->expo);
	return (0);
}
