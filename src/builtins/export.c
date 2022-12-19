#include <minishell.h>

int32_t	varname_len(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);

}
void	print_expo(char **expo)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	while (expo[i])
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		j = varname_len(expo[i]);
		write(STDOUT_FILENO, expo[i], j);
		if (j && expo[i][j + 1])
		{
			write(STDOUT_FILENO, "=", 1);
			printf("\"%s\"\n", &expo[i][j + 1]);
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	sort_export(char **expo)
{
	int32_t	i;
	int32_t	smallest;
	char	*tmp;

	i = 0;
	while (expo[i])
	{
		if (expo[i + 1])
		{
			smallest = varname_len(expo[i]);
			if (smallest > varname_len(expo[i + 1]))
				smallest = varname_len(expo[i + 1]);
			if (ft_strncmp(expo[i], expo[i + 1], smallest) > 0)
			{
				tmp = expo[i];
				expo[i] = expo[i + 1];
				expo[i + 1] = tmp;
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

bool	has_equals(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	valid_var(char *str)
{
	int32_t	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	export_error(char *str)
{
	write(STDERR_FILENO, "Minishell: export: `", 21);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\': not a valid identifier\n", 27);
}

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

static int	in_env(char *argument, char **env)
{
	int		i;
	char	*var_name;

	var_name = calloc(varname_len(argument) + 1, sizeof(char));
	if (var_name)
		ft_strlcpy(var_name, argument, varname_len(argument) + 1);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var_name, env[i], ft_strlen(var_name)))
			return (free(var_name), 1);
		else if (!ft_strncmp(var_name, env[i], ft_strlen(var_name) + 1))
			return (free(var_name), 1);
		i++;
	}
	free(var_name);
	return (0);
}

void	export_add(char **arguments, t_minishell *shell)
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
		export_add(arguments, shell);
	else
		print_expo(shell->expo);
	return (0);
}
