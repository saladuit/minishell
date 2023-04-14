#include <minishell.h>

int32_t	ft_echo(char **arguments, t_minishell *shell)
{
	size_t	i;
	bool	newline;

	(void)shell;
	newline = true;
	i = 1;
	if (arguments[i] && !ft_strncmp(arguments[i], "-n", 2))
	{
		newline = false;
		i++;
	}
	while (arguments[i])
	{
		write(STDOUT_FILENO, arguments[i], ft_strlen(arguments[i]));
		i++;
		if (arguments[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
