#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		write(STDERR_FILENO, (char *)message_lookup(E_USAGE), 7);
		if (argv)
			ft_putendl_fd(*argv, STDERR_FILENO);
		else
			ft_putendl_fd("sheldon", STDERR_FILENO);
		exit(E_USAGE);
	}
	return (minishell(envp));
}
