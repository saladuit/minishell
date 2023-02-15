#include <minishell.h>
#include "libft.h"

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

void envp_clear_load(char *key, char *value, char **entry)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (entry)
		free(entry);
}

// FIXME this should be moved to its own file
static void envp_load(t_dictionary *env, char **envp)
{
	char **entry;
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		entry = ft_split(envp[i], '=');
		if (!entry)
		{
			i++;
			continue;
		}
		dict_set(env, entry[0], entry[1]);
		envp_clear_load(NULL, NULL, entry);
		i++;
	}
}

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
	return (0);
}
