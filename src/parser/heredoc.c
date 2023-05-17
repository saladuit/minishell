/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:27:00 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:27:02 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define HEREDOC_PROMPT "> "

static void	print_heredoc_error(char *delimiter)
{
	ft_putstr_fd("sheldon: warning: here-document", STDERR_FILENO);
	ft_putstr_fd(" at line 5 delimited by end-of-file", STDERR_FILENO);
	ft_putstr_fd(" (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	print_line(char *line, int32_t fd_write_end)
{
	ft_putstr_fd(line, fd_write_end);
	ft_putstr_fd("\n", fd_write_end);
}

int32_t	here_doc(char *delimiter, int fd_write_end)
{
	char	*line;

	if (!delimiter || *delimiter == '\0')
		return (ERROR);
	signal(SIGINT, signal_ctrl_c_heredoc);
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			print_heredoc_error(delimiter);
			_exit(SUCCESS);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		print_line(line, fd_write_end);
		free(line);
	}
	return (SUCCESS);
}
