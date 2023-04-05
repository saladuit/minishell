#include <minishell.h>

void	ft_exit(char **args, t_minishell *shell)
{
	if (args[1] != NULL)
	{
		shell->status = ft_atoi(args[1]) % 256;
	}
	shell->stop = true;
}
