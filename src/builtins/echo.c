#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <libft.h>

int32_t	ft_echo(char **arguments, char **envp)
{
	int32_t	i;
	bool	newline;

	(void)envp;
	newline = true;
	i = 1;
	if (!ft_strncmp(arguments[i], "-n\0", 3))
	{
		newline = false;
		i++;
	}
	while (arguments[i])
	{
		write(1, arguments[i], ft_strlen(arguments[i]));
		i++;
		if (arguments[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
