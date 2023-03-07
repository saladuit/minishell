#include <minishell.h>

char	*make_heredoc_file(int32_t *fd)
{
	char			*filename;
	char			*num_str;
	static int32_t	i;

	i = 0;
	num_str = ft_itoa(i);
	filename = ft_strjoin("/tmp/.heredoc", num_str);
	free(num_str);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	i++;
	return (filename);
}

char	*wait_for_line(void)
{
	char	*line;

	line = NULL;
	write(STDOUT_FILENO, "Heredoc>", 9);
	while (!line)
		line = get_next_line(STDIN_FILENO);
	return (line);
}

bool	is_phrase(char *phrase, char *read_line)
{
	size_t	i;

	i = 0;
	while (read_line[i])
	{
		if (i == ft_strlen(phrase) && !ft_strncmp(phrase, read_line,
				ft_strlen(phrase) - 1) && read_line[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

void	heredoc_loop(char *phrase, int32_t fd)
{
	char	*read_line;

	reset_signals();
	read_line = calloc(1, 1);
	while (true)
	{
		free(read_line);
		read_line = wait_for_line();
		if (read_line)
		{
			if (is_phrase(phrase, read_line))
				exit(0);
			write(fd, read_line, ft_strlen(read_line));
		}
	}
	exit(0);
}

//TODO add heredoc signal interuption
char	*add_heredoc(char *phrase)
{
	char	*filename;
	int32_t	fd;
	pid_t	id;
	int32_t	status;

	// setup_signals(SHEREDOC);
	if (g_exitcode == 300)
		return (NULL);
	filename = make_heredoc_file(&fd);
	id = fork();
	if (id == -1)
		return (NULL);
	if (id == 0)
		heredoc_loop(phrase, fd);
	waitpid(id, &status, WUNTRACED);
	free(phrase);
	return (close(fd), filename);
}
