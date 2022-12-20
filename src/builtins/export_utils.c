#include <minishell.h>

void	export_error(char *str)
{
	write(STDERR_FILENO, "Minishell: export: `", 21);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\': not a valid identifier\n", 27);
}

int32_t	varname_len(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int32_t	in_env(char *argument, char **env)
{
	int32_t	i;
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
