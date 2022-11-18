#include <stdio.h>
#include <stdbool.h>

void	echo(int32_t in_fd, int32_t out_fd, char **arguments, char **envp)
{
	int32_t	i;
	bool	newline;

	newline = true;
	close(in_fd);
	if (ft_strlcmp())

	while (arguments[i])
	{
		write(out_fd, arguments[i], ft_strlen(arguments[i]));
		write(out_fd, " ", 1);
		i++;
	}
}
