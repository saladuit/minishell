#include <minishell.h>

static void envp_clear(char *key, char *value, char **entry)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (entry)
		free(entry);
}

void envp_load(t_dictionary *env, char **envp)
{
	char **entry;
	int	   i;

	i = 0;
	while (envp[i] != NULL)
	{
		entry = ft_split(envp[i], '=');
		if (!entry)
		{
			i++;
			envp_clear(entry[0], entry[1], entry);
			continue;
		}
		dict_set(env, entry[0], entry[1]);
		envp_clear(NULL, NULL, entry);
		i++;
	}
	if (DEBUG)
		dict_print(env);
}
