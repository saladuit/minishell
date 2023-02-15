#include <minishell.h>

//int32_t	dup_envp(t_minishell *shell, char **envp)
//{
//	int32_t	i;
//
//	i = 0;
//	while (envp[i])
//		i++;
//	shell->env = calloc((i + 1), sizeof(char *));
//	shell->expo = calloc((i + 1), sizeof(char *));
//	if (!shell->env || !shell->expo)
//		return (1);
//	i = 0;
//	while (envp[i])
//	{
//		shell->env[i] = ft_strdup(envp[i]);
//		shell->expo[i] = ft_strdup(envp[i]);
//		if (!shell->env[i] || !shell->expo)
//			return (1);
//		i++;
//	}
//	sort_export(shell->expo);
//	return (0);
//}

// FIXME this should be moved to its own file called envp.c
static void envp_clear(char *key, char *value, char **entry)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (entry)
		free(entry);
}

// FIXME this should be moved to its own file called envp.c
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
