#include <minishell.h>

static void env_err_msg(char *msg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

int	ft_env(char **arguments, t_minishell *shell)
{
	if (arguments[1])
	{
		shell->status = E_COMMAND_NOT_FOUND;
		env_err_msg(arguments[1]);
		return (shell->status);
	}
	dict_print(&shell->env);
	return (0);
}
