#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

char	**dup_envp(char **envp)
{
	int32_t	i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	return (env);
}
