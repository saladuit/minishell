#include <minishell.h>

int32_t	here_doc(char *delimiter, int fd_write_end)
{
	char	*line;

	if (!delimiter || ft_strlen(delimiter) == 0)
		return (ERROR);
	while (1)
	{
		signal(SIGINT, signal_ctrl_c_heredoc);
		line = readline("> ");
		if (!line)
			_exit(E_COMMAND_NOT_FOUND);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write_end, line, ft_strlen(line));
		write(fd_write_end, "\n", 1);
		free(line);
	}
	return (SUCCESS);
}
