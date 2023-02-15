#include <minishell.h>
#include <unistd.h>
#include "libft.h"

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

int	ft_unset(char **arguments, t_minishell *shell)
{
	int i;

	i = 0;
    if (arguments[i++] == NULL)
	{
        ft_putstr_fd("unset: error: no variable name provided\n", STDERR_FILENO);
		shell->exit_code = E_BUILTIN;
        return (E_BUILTIN);
    }
	while (arguments[i])
	{
        dict_delete(&shell->envd, arguments[i]);
		i++;
    }
	return (0);
}
