#include <minishell.h>
#include <message.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
*/

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sheldon;

	(void)argv;
	sheldon.exit_code = 0;
	if (argc > 1)
		ft_minishell_exit(USAGE);
	while (1)
		minishell(&sheldon, envp);
}
