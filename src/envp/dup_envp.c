#include <minishell.h>

int32_t	dup_envp(t_minishell *shell, char **envp)
{
	int32_t	i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = calloc((i + 1), sizeof(char *));
	shell->expo = calloc((i + 1), sizeof(char *));
	if (!shell->env || !shell->expo)
		return (1);
	i = 0;
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		shell->expo[i] = ft_strdup(envp[i]);
		if (!shell->env[i] || !shell->expo)
			return (1);
		i++;
	}
	sort_export(shell->expo);
	return (0);
}
