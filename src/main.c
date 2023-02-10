#include <minishell.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

static void load_envp(t_dictionary *env, char **envp)
{
	dict_init(env);
	for (int i = 0; envp[i] != NULL; i++)
	{
		char *entry = strdup(envp[i]);
		char *key = strtok(entry, "=");
		char *value = strtok(NULL, "=");
		printf("entry: %s\n", entry);
		printf("key: %s\n", key);
		printf("value: %s\n", value);
		dict_set(env, key, value);
		free(entry);
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
