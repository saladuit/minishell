#include <minishell.h>

int	ft_env(char **arguments, t_minishell *shell)
{
	(void)arguments;
	dict_print(&shell->env);
	return (0);
}
