#include <minishell.h>
#include <stdlib.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
*/

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sheldon;

	(void)argv;
	if (argc > 1)
    ft_minishell_exit(USAGE, EXIT_FAILURE);
	if (dup_envp(&sheldon, envp))
    perror("Environment parsing: ");
	if (!isatty(STDIN_FILENO))
  		perror("tty: ");
	sheldon.exit_code = 0;
	while (1)
		minishell(&sheldon);
}
