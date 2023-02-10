#include <minishell.h>

int	ft_exit(char **arguments, t_minishell *shell)
{
	(void)arguments;
	(void)shell;
	rl_clear_history();
	if (arguments[1])
			exit((unsigned short)ft_atoi(arguments[1]));
	else
		exit(0);
	return (0);
}
