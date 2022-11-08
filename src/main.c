#include <minishell.h>
#include <message.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
		ft_minishell_exit(USAGE);
	while (1)
		minishell(envp);
}
