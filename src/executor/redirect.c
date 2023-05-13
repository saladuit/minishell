/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   redirect.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 15:33:44 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 15:33:44 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int32_t	redirect_file_descriptor(int source_fd, t_type redirection)
{
	if (redirection == INPUT || redirection == HEREDOC)
		return (dup2(source_fd, STDIN_FILENO));
	else
		return (dup2(source_fd, STDOUT_FILENO));
}

static int32_t	redirect(t_redir *redir, t_type type)
{
	int32_t	fd;

	fd = open_fd_type(redir->filename, type);
	if (fd == ERROR)
		return (ERROR);
	if (redirect_file_descriptor(fd, type) == ERROR)
	{
		message_system_call_error("redirect");
		close(fd);
		return (ERROR);
	}
	return (fd);
}

static int32_t	close_fd_if_open(int32_t *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (SUCCESS);
}

static bool	handle_redirection(t_redir *redir, int32_t *input_fd,
		int32_t *output_fd)
{
	int32_t	ret;

	ret = redirect(redir, redir->type);
	if (ret == ERROR)
		return (false);
	if (redir->type == INPUT || redir->type == HEREDOC)
	{
		close_fd_if_open(input_fd);
		*input_fd = ret;
	}
	else
	{
		close_fd_if_open(output_fd);
		*output_fd = ret;
	}
	return (true);
}

int32_t	setup_redirects(t_command *command)
{
	t_redir	*redir;
	int32_t	i;
	int32_t	input_fd;
	int32_t	output_fd;

	i = 0;
	input_fd = -1;
	output_fd = -1;
	while (i < command->n_redirs)
	{
		get_next_redir(command, &redir);
		if (handle_redirection(redir, &input_fd, &output_fd) == false)
		{
			close_fd_if_open(&input_fd);
			close_fd_if_open(&output_fd);
			return (E_GENERAL);
		}
		i++;
	}
	return (SUCCESS);
}
