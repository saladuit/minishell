/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   open.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 15:00:30 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 15:00:30 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int32_t	open_heredoc(char *path)
{
	return (here_doc(path));
}

static int32_t	open_input(char *path)
{
	return (open(path, O_RDONLY));
}

static int32_t	open_output(char *path)
{
	return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664));
}

static int32_t	open_append(char *path)
{
	return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0664));
}

int32_t	open_fd_type(char *path, t_type type)
{
	if (type == HEREDOC)
		return (open_heredoc(path));
	else if (type == INPUT)
		return (open_input(path));
	else if (type == OUTPUT)
		return (open_output(path));
	else if (type == APPEND)
		return (open_append(path));
	else
	{
		ft_putstr_fd("Wrong option in open_fd_type", STDERR_FILENO);
		exit(EXIT_FAILURE);
		return (false);
	}
}
