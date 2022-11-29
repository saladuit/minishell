#include <stdlib.h>
#include <stdio.h>

int	ft_env(char **arguments, char **envp)
{
	int32_t	i;

	(void)arguments;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
