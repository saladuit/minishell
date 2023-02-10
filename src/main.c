#include <minishell.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */
int g_exitcode;

//void leaks_check(void)
//{
//	system("leaks -q minishell.out");
//}

int	main(int argc, char **argv, char **envp)
{
//	atexit(leaks_check);
	t_minishell sheldon;

	(void)argv;
	(void)envp;
	if (argc > 1)
		ft_minishell_exit(USAGE, EXIT_FAILURE);
//	if (dup_envp(&sheldon, envp))
//		perror("Environment parsing: ");
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	// sheldon.exit_code = 0;
	g_exitcode = 0;
	while (minishell(&sheldon));
	rl_clear_history();
	return (0);
}
