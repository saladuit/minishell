#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <minishell.h>

int ft_exit(char **arguments, t_minishell *shell)
{
	(void)arguments;
	(void)shell;
	rl_clear_history();
	exit(0);
	return (0);
}
