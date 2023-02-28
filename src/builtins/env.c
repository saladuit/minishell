#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_env(char **arguments, t_minishell *shell)
{
	(void)arguments;
	dict_print(&shell->envd);
	return (0);
}
