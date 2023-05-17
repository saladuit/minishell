/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:06:10 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/04 19:06:12 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	check_flag(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i++] != '-')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

static void	process_args(char **arguments, size_t *i)
{
	size_t	arg_index;

	arg_index = 0;
	while (arguments[*i + arg_index])
	{
		if (arg_index >= 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, arguments[*i + arg_index],
			ft_strlen(arguments[*i + arg_index]));
		arg_index++;
	}
}

static void	process_flags(char **arguments, size_t *i,
		bool *no_trailing_newline)
{
	while (arguments[*i] && check_flag(arguments[*i]))
	{
		*no_trailing_newline = true;
		(*i)++;
	}
}

void	ft_echo(char **arguments, t_minishell *shell)
{
	size_t	i;
	bool	no_trailing_newline;

	i = 1;
	(void)shell;
	no_trailing_newline = false;
	if (!arguments[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	process_flags(arguments, &i, &no_trailing_newline);
	process_args(arguments, &i);
	if (!no_trailing_newline)
		write(STDOUT_FILENO, "\n", 1);
}
