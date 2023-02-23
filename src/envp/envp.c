#include <minishell.h>

static char *envp_load_value(char *key)
{
	char *value;

	value = ft_strchr(key, '=');
	if (value == NULL)
		value = ft_strdup("");
	else
	{
		*value = '\0';
		value = ft_strdup(++value);
	}
	if (value == NULL)
	{
		free(key);
		handle_system_call_error("envp_load_key");
	}
	return (value);
}

int32_t envp_load(t_dictionary *env, char **envp)
{
	char *key;
	char *value;
	int	  i;

	i = 0;
	while (envp[i] != NULL)
	{
		key = ft_strdup(envp[i++]);
		if (key == NULL)
			return (handle_system_call_error("envp_load_key"));
		value = envp_load_value(key);
		if (value == NULL)
			return (handle_system_call_error("envp_load_value"));
		if (dict_set(env, key, value) == ERROR)
		{
			free(value);
			free(key);
			return (handle_system_call_error("dict_set"));
		}
	}
	return (SUCCESS);
}
