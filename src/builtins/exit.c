#include <minishell.h>

int	ft_exit(char **arguments, t_minishell *shell)
{
	(void)arguments;
	(void)shell;
	rl_clear_history();
	exit(ft_atoi(arguments[1]));
	return (0);
}
