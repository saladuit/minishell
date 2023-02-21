#include <minishell.h>

void envp_load(t_dictionary *env, char **envp)
{
	char *key;
	char *value;
	int	  i;

	i = 0;
	while (envp[i] != NULL)
	{
		key = ft_strdup(envp[i]);
		if (key == NULL)
		{
			ft_putstr_fd("Env: error: out of memory\n", STDERR_FILENO);
			i++;
			break;
		}
		value = ft_strchr(key, '=');
		if (value == NULL)
			value = ft_strdup("");
		else
		{
			*value = '\0';
			value = ft_strdup(++value);
		}
		if (!value)
		{
			free(key);
			ft_putstr_fd("Env: error: out of memory\n", STDERR_FILENO);
			break;
		}
		if (dict_set(env, key, value) == ERROR)
		{
			free(value);
			free(key);
			ft_putstr_fd("Env: error: out of memory\n", STDERR_FILENO);
			break;
		}
		i++;
	}
	if (DEBUG)
		dict_print(env);
}
