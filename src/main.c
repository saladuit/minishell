#include <minishell.h>
#include "libft.h"

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
 */

void clear_envp_load(char *key, char *value, char **entry)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (entry)
		free(entry);
}
static void load_envp(t_dictionary *env, char **envp)
{
	char **entry;
	char  *key;
	char  *value;
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		entry = ft_split(envp[i], '=');
		if (!entry)
			continue;
		key = ft_strdup(entry[0]);
		if (!entry[1])
			value = ft_strdup("");
		else
			value = ft_strdup(entry[1]);
		if (!key || !value)
		{
			clear_envp_load(key, value, entry);
			continue;
		}
		dict_set(env, key, value);
		clear_envp_load(key, NULL, NULL);
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
