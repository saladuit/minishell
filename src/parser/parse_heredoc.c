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

int32_t	here_doc(char *delimiter, int fd_write_end)
{
	char	*line;

	if (!delimiter || ft_strlen(delimiter) == 0)
		return (ERROR);
	signal(SIGINT, signal_ctrl_c_heredoc);
	while (1)
	{
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
