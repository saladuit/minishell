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

static bool	numeric(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (false);
	while (arg[i] && arg[i] == '0')
		i++;
	while (arg[i] && arg[i] != '#' && arg[i] != ';')
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	handle_count_is_bigger_then_two(char **args, t_status *status,
											bool *stop)
{
	if (numeric(args[1]) == true || ft_strncmp(args[1], "?", 2) == 0)
	{
		*status = E_GENERAL;
		exit_err_msg(NULL);
		*stop = false;
	}
	else
	{
		*status = E_UNKNOWN;
		exit_err_msg(args[1]);
		*stop = true;
	}
}

static void	handle_count_equals_two(char **args, t_status *status)
{
	long	res;

	if (ft_strlen(args[1]) == 0 || !ft_strncmp(args[1], "--", 3))
		*status = E_USAGE;
	else if (ft_strncmp(args[1], "?", 2) == 0)
		*status = E_GENERAL;
	else if (!numeric(args[1]) || (!ft_ltoi_with_overflow(args[1], &res)))
	{
		*status = E_UNKNOWN;
		exit_err_msg(args[1]);
	}
	else
	{
		*status = (t_status) ft_atoi(args[1]) % 256;
		if (*status < 0)
			*status += 256;
	}
}

void	ft_exit(char **args, t_minishell *shell)
{
	size_t		count;
	bool		stop;

	stop = true;
	count = ft_str_count(args);
	if (count > 2)
		handle_count_is_bigger_then_two(args, &shell->status, &stop);
	if (count == 2 && stop == true)
		handle_count_equals_two(args, &shell->status);
	if (shell->is_pipeline)
		_exit(shell->status);
	if (stop == true)
		shell->stop = true;
}
