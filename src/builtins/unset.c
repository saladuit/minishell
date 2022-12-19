#include <minishell.h>

// static int	in_env(char *var_name, char **env)
// {
// 	int		i;
// 	char	*suffix;
// 	char	*var;

// 	i = 0;
// 	suffix = ft_strdup("=");
// 	while (suffix && env[i])
// 	{
// 		var = ft_strjoin(var_name, suffix);
// 		if (var && !ft_strncmp(var, env[i],
// 				ft_strlen(var)))
// 			return (1);
// 		free(var);
// 		i++;
// 	}
// 	return (0);
// }

static int	in_args(char **argv, char *env_line)
{
	int		i;
	char	*suffix;
	char	*var;

	i = 1;
	suffix = ft_strdup("=");
	while (suffix && argv[i])
	{
		var = ft_strjoin(argv[i], suffix);
		if (var
			&& !ft_strncmp(var, env_line, ft_strlen(var)))
			return (free(suffix), 1);
		free(var);
		if (argv[i]
			&& !ft_strncmp(argv[i], env_line, ft_strlen(argv[i]) + 1))
			return (free(suffix), 1);
		i++;
	}
	free(suffix);
	return (0);
}

void	unset_copy(char **argv, char **new_env, char **old_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (!in_args(argv, old_env[i]))
		{
			new_env[j] = old_env[i];
			j++;
		}
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
}

static int	get_env_len(char **arguments, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (env[i])
	{
		if (!in_args(arguments, env[i]))
			len++;
		i++;
	}
	return (len);
}

int	ft_unset(char **arguments, t_minishell *shell)
{
	char	**new_env;
	char	**new_expo;

	new_env = malloc(get_env_len(arguments, shell->env) * sizeof(char *));
	new_expo = malloc(get_env_len(arguments, shell->expo) * sizeof(char *));
	if (!new_env || !new_expo)
		return (1);
	unset_copy(arguments, new_env, shell->env);
	unset_copy(arguments, new_expo, shell->expo);
	free(shell->env);
	free(shell->expo);
	shell->env = new_env;
	shell->expo = new_expo;
	return (0);
}
