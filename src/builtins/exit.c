#include <minishell.h>

static void exit_err_msg(char *arg)
{
	ft_putstr_fd(SHELDON, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	if (!arg)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
}

static int numeric(char *arg)
{
	size_t i;

	i = 0;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	while (arg[i] && arg[i] == '0')
		i++;
	if (arg[i] == '-')
		i++;
	while (arg[i] && arg[i] != '#' && arg[i] != ';')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static size_t count_args(char **args)
{
	size_t count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	ft_exit(char **args, t_minishell *shell)
{
	long long	res;
	size_t		count;

	count = count_args(args);
	if (count > 2)
	{
		shell->status = E_GENERAL;
		exit_err_msg(NULL);
		return ;
	}
	if (count == 2)
	{
		if (!numeric(args[1]) || (!ft_ltoi_with_overflow(args[1], &res)))
		{
			shell->status = E_UNKNOWN;
			exit_err_msg(args[1]);
		}
		else
			shell->status = (t_status) ft_atoi(args[1]) % 256;
	}
	if (shell->is_pipeline)
		_exit(shell->status);
	shell->stop = true;
	return ;
}
