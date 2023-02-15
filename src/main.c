#include <minishell.h>
#include <stdlib.h>
#include "libft.h"

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

static void init_sheldon(t_minishell *sheldon, char **envp)
{
	bzero(sheldon, sizeof(t_minishell));
	envp_load(&sheldon->envd, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell sheldon;

	(void)argv;
	if (argc > 1)
		ft_minishell_exit(USAGE, EXIT_FAILURE);
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	init_sheldon(&sheldon, envp);
	while (minishell(&sheldon));
	dict_destroy(&sheldon.envd);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
