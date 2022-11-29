#include <minishell.h>
#include <libft.h>

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
		if (var && !ft_strncmp(var, env_line,
				ft_strlen(var)))
			return (1);
		free(var);
		i++;
	}
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

static int	get_env_len(char **arguments, t_minishell *shell)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (shell->env[i])
	{
		if (!in_args(arguments, shell->env[i]))
			len++;
		i++;
	}
	return (len);
}

int	ft_unset(char **arguments, t_minishell *shell)
{
	char	**new_env;
	int		env_len;

	env_len = get_env_len(arguments, shell);
	new_env = malloc(env_len * sizeof(char *));
	if (!new_env)
		return (1);
	unset_copy(arguments, new_env, shell->env);
	free(shell->env);
	shell->env = new_env;
	return (0);
}
