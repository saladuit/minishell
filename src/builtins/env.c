#include <stdlib.h>
#include <stdio.h>
#include <minishell.h>

int	ft_env(char **arguments, t_minishell *shell)
{
	int32_t	i;

	(void)arguments;
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
