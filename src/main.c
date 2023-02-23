#include <minishell.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

static int32_t	init_sheldon(t_minishell *sheldon, char **envp)
{
	int32_t	exit_status;
	ft_bzero(sheldon, sizeof(t_minishell));
	exit_status = envp_load(&sheldon->envd, envp);
	if (DEBUG)
		dict_print(&sheldon->envd);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sheldon;

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd((char *)messages_lookup(E_USAGE), STDERR_FILENO);
		exit(E_USAGE);
	}
	sheldon.exit_code = init_sheldon(&sheldon, envp);
	if (!isatty(STDIN_FILENO))
	{
		sheldon.exit_code = handle_system_call_error("isatty");
		rl_outstream = stdin;
	}
	while (minishell(&sheldon))
		;
	dict_destroy(&sheldon.envd);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
