#include <minishell.h>

int	ft_exit(char **args, t_minishell *shell)
{
	int	status;

	status = EXIT_SUCCESS;
	(void)shell;
	if (args[1] != NULL)
	{
		status = atoi(args[1]) % 256;
	}
	return (status);
}
