#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int ft_exit(char **arguments, char **envp)
{
	(void)arguments;
	(void)envp;
	rl_clear_history();
	exit(0);
	return (0);
}
