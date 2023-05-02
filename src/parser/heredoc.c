#include <minishell.h>

static void	exit_d_check(char *line, bool *exit)
{
	if (!line)
		*exit = true;
}

int32_t	here_doc(char *delimiter)
{
	int		fd[2];
	char	*line;
	bool	exit;

	if (!delimiter || ft_strlen(delimiter) == 0)
		return (ERROR);
	if (pipe(fd) == -1)
		return (ERROR);
	exit = false;
	while (exit == false)
	{
		line = readline("> ");
		exit_d_check(line, &exit);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	if (exit)
		return (free(line), close(fd[0]), ERROR);
	return (fd[0]);
}
