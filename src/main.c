#include <minishell.h>
#include <message.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
*/

int	main(int argc, char **argv, char **envp)
{
	int32_t exit_status;

	(void)argv;
	if (argc > 1)
		ft_minishell_exit(USAGE);
	while (1)
		exit_status = minishell(envp);
	return (ft_minishell_exit(exit_status));
}
