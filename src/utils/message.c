/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:39 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:39 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char	*message_lookup(t_status status)
{
	const char	*message[] = {
	[E_USAGE] = "usage: ",
	[E_GENERAL] = "operation not permitted",
	[E_BUILTIN] = "no such file or directory",
	[E_EXEC] = "permission problem or command is not an executable",
	[E_COMMAND_NOT_FOUND] = "command not found",
	[E_EXIT_INVALID_ARG] = "numeric argument required",
	[E_CTRL_C] = "script terminated by Control-C",
	[E_UNKNOWN] = "unknown error code",
	[E_UNEXPECTED_TOKEN] = "syntax error near unexpected token `",
	[E_QUOTES] = "quote is unclosed",
	};

	return (message[status]);
}

static void	message_unexpected_token(const char *token)
{
	ft_putstr_fd((char *)message_lookup(E_UNEXPECTED_TOKEN), STDERR_FILENO);
	ft_putstr_fd((char *)token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

t_status	message_general_error(t_status status, const char *msg)
{
	ft_putstr_fd(E_SHELDON, STDERR_FILENO);
	if (status == E_UNEXPECTED_TOKEN)
		message_unexpected_token(msg);
	else
		ft_putendl_fd((char *)message_lookup(status), STDERR_FILENO);
	return (status);
}

// t_status	message_child_status(t_status status)
// {
// 	if (WIFEXITED(status))
// 	{
// 		status = WEXITSTATUS(status);
// 		ft_putendl_fd((char *)message_lookup(status), STDERR_FILENO);
// 	}
// 	return (status);
// }

// void	message_signal(t_status signal_num)
// {
// 	if (WIFSIGNALED(signal_num))
// 	{
// 		signal_num = WTERMSIG(signal_num);
// 		ft_putstr_fd("Received signal ", STDERR_FILENO);
// 		ft_putstr_fd("%d", STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		ft_putstr_fd(strsignal(signal_num), STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		exit(signal_num + E_FATAL_SIGNAL);
// 	}
// }

t_status	message_system_call_error(const char *function_name)
{
	ft_putstr_fd(E_SHELDON, STDERR_FILENO);
	ft_putstr_fd((char *)function_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (E_GENERAL);
}
