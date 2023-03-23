#include <minishell.h>

static void	handle_signal(int32_t signal_num)
{
	ft_putstr_fd("Received signal ", STDERR_FILENO);
	ft_putstr_fd("%d", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strsignal(signal_num), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(signal_num + E_FATAL_SIGNAL);
}

int32_t	handle_mini_errors(t_exitstatus status)
{
	int32_t	exit_status;
	int32_t	signal_num;

	if (status)
		ft_putendl_fd((char *)messages_lookup(status), STDERR_FILENO);
	else if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		ft_putendl_fd((char *)messages_lookup(exit_status), STDERR_FILENO);
	}
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		handle_signal(signal_num);
	}
	return (status);
}

const char	*messages_lookup(t_exitstatus status)
{
	const char *message[] = {
		[E_USAGE] = "Usage: ",
		[E_GENERAL] = "Operation not permitted",
		[E_BUILTIN] = "No such file or directory",
		[E_EXEC] = "Permission problem or command is not an executable",
		[E_COMMAND_NOT_FOUND] = "Command not found",
		[E_EXIT_INVALID_ARG] = "numeric argument required",
		[E_CTRL_C] = "Script terminated by Control-C",
		[E_UNKNOWN] = "Unknown error code",
        [E_UNEXPECTED_TOKEN] = "Minishell: bash: syntax error near unexpected token",
	};
	return (message[status]);
}

int32_t	handle_system_call_error(const char *function_name)
{
	ft_putstr_fd((char *)function_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (E_GENERAL);
}
