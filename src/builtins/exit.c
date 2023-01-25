#include <minishell.h>

int	ft_exit(char **arguments, t_minishell *shell)
{
	int	return_code;
	(void)arguments;
	(void)shell;
	rl_clear_history();
	if (arguments[1])
	{
		return_code = ft_atoi(arguments[1]);
		if (return_code < 0 || return_code > 255)
			exit(return_code);
	}
	else
		exit(0);
	return (0);
}
