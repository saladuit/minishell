#include <minishell.h>

// check !line later, now resolving a segfault
// error code CNTRL_D = -2 could be a solution
int32_t	here_doc(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (!delimiter || ft_strlen(delimiter) == 0)
		return (ERROR);
	if (pipe(fd) == -1)
		return (ERROR);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);
			return (ERROR);
		}
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
	return (fd[0]);
}
