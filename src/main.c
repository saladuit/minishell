#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		write(STDERR_FILENO, (char *)messages_lookup(E_USAGE), 7);
		ft_putendl_fd(*argv, STDERR_FILENO);
		exit(E_USAGE);
	}
	return (minishell(envp));
}
