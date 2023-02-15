#include <stdlib.h>
#include <stdio.h>
#include <minishell.h>

int	ft_env(char **arguments, t_minishell *shell)
{
	(void)arguments;
	dict_print(&shell->envd);
	return (0);
}
