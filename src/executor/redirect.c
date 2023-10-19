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

static int32_t redirect(t_redir *redir, t_type type)
{
	int32_t fd;

	fd = open_fd_type(redir->filename, type);
	if (fd == ERROR)
		return (ERROR);
	return (fd);
}

static int32_t close_fd_if_open(int32_t *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (SUCCESS);
}

static bool handle_redirection(
	t_redir *redir, int32_t *input_fd, int32_t *output_fd)
{
	int32_t ret;

	if (input_fd == NULL && redir->type == INPUT)
		return (false);
	ret = redirect(redir, redir->type);
	if (ret == ERROR)
		return (false);
	if (input_fd != NULL && (redir->type == INPUT || redir->type == HEREDOC))
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

int32_t redirect_fds(int32_t input_fd, int32_t output_fd)
{
	int32_t status;

	status = SUCCESS;
	if (input_fd != ERROR)
		status = dup2(input_fd, STDIN_FILENO);
	if (status != ERROR && output_fd != ERROR)
		status = dup2(output_fd, STDOUT_FILENO);
	return (status);
}

void set_simple_builtin_output(t_command *command, t_minishell *shell)
{
	t_redir *redir;
	int32_t	 i;
	int32_t	 output_fd;

	i = 0;
	output_fd = -1;
	while (i < command->n_redirs)
	{
		get_next_redir(command, &redir);
		if (handle_redirection(redir, NULL, &output_fd) == false)
			close_fd_if_open(&output_fd);
		i++;
	}
	if (output_fd != -1)
		shell->out_fd = output_fd;
	else
		shell->out_fd = STDOUT_FILENO;
}

int32_t setup_redirects(t_command *command)
{
	t_redir *redir;
	int32_t	 i;
	int32_t	 input_fd;
	int32_t	 output_fd;

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
	if (redirect_fds(input_fd, output_fd) == ERROR)
		return (E_GENERAL);
	return (SUCCESS);
}
