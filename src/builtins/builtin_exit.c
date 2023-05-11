/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:06:52 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/04 19:06:54 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	numeric(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0' || arg[i] == '-')
		return (0);
	while (arg[i] && arg[i] == '0')
		i++;
	while (arg[i] && arg[i] != '#' && arg[i] != ';')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_err_msg(char *arg)
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

static size_t	count_args(char **args)
{
	size_t	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static t_status	check_edge_cases(char **args)
{
	if ((ft_strncmp(args[1], "--", 3) == 0 && ft_strncmp(args[2], "--", 3) == 0)
			|| ft_strncmp(args[1], "-", 2) == 0 || ft_strncmp(args[1], "+", 2) == 0)
		return (E_UNKNOWN);
	if (ft_strncmp(args[1], "--", 3) == 0)
		return (E_USAGE);
	if (ft_strncmp(args[1], "?", 2) == 0)
		return (E_GENERAL);
	return (E_NO_STATUS);
}

void	ft_exit(char **args, t_minishell *shell)
{
	long long	res;
	size_t		count;
	t_status	status;

	count = count_args(args);
	if (count > 1 && check_edge_cases(args) != E_NO_STATUS)
	{
		status = check_edge_cases(args);
		if (status != E_NO_STATUS)
			shell->status = status;
	}
	else if (count == 2)
	{
		if (args[1][0] == '$')
			shell->status = E_UNKNOWN;
		else if (ft_strlen(args[1]) == 0)
			shell->status = E_GENERAL;
		else if (!numeric(args[1]) || (!ft_ltoi_with_overflow(args[1], &res)))
		{
			shell->status = E_UNKNOWN;
			exit_err_msg(args[1]);
		}
		else
			shell->status = (t_status)ft_atoi(args[1]) % 256;
	}
	else if (count > 2 && ft_strbapi(args[1], (bool (*)(int)) &ft_isdigit))
	{
		shell->status = E_GENERAL;
		exit_err_msg(NULL);
		return ;
	}
	else if (count > 2)
	{
		shell->status = E_UNKNOWN;
		exit_err_msg(args[1]);
	}
	if (shell->is_pipeline)
		_exit(shell->status);
	shell->stop = true;
	return ;
}
