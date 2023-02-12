#include <minishell.h>
#include "libft.h"

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

static void load_envp(t_dictionary *env, char **envp)
{
	char **entry;
	int i;

	i = 0;
	dict_init(env);
	while (envp[i] != NULL)
	{
		entry = ft_split(envp[i], '=');
		printf("key: %s\n", entry[i]);
		printf("value: %s\n", entry[i]);
		dict_set(env, entry[i], entry[i + 1]);
		free(entry);
		i++;
	}
}

static void init_sheldon(t_minishell *sheldon, char **envp)
{
	bzero(sheldon, sizeof(t_minishell));
	load_envp(&sheldon->envd, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell sheldon;

	(void)argv;
	(void)envp;
	if (argc > 1)
		ft_minishell_exit(USAGE, EXIT_FAILURE);
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	init_sheldon(&sheldon, envp);
	while (minishell(&sheldon));
	rl_clear_history();
	return (0);
}
