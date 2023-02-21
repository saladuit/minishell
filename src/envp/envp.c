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
			ft_putstr_fd("export: error: out of memory\n", STDERR_FILENO);
			dict_destroy(env);
//			exit(1); //FIXME
			i++;
			continue ;
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
			dict_destroy(env);
//			exit(1); //FIXME
			i++;
			continue;
		}
		if (dict_set(env, key, value) == ERROR)
		{
			free(value);
			free(key);
			dict_destroy(env);
//			exit(1); //FIXME
		}
		i++;
	}
	if (DEBUG)
		dict_print(env);
}
