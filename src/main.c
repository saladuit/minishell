#include <minishell.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

static void	init_sheldon(t_minishell *sheldon, char **envp)
{
	bzero(sheldon, sizeof(t_minishell));
	envp_load(&sheldon->envd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sheldon;
	int32_t		i;

	i = 0;
	(void)argv;
	if (argc > 1)
	{
		ft_minishell_message(USAGE, EXIT_FAILURE);
		exit(1);
	}
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	init_sheldon(&sheldon, envp);
	while (i != 1 && minishell(&sheldon))
		i++;
	dict_destroy(&sheldon.envd);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
