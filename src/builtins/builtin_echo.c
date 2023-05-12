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

static void	write_arg(char *arg)
{
	write(STDOUT_FILENO, arg, ft_strlen(arg));
}

static bool check_flag(char *arg)
{
    size_t  i;

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

void	ft_echo(char **arguments, t_minishell *shell)
{
	size_t	i;
	bool	no_trailing_newline;

	i = 1;
	(void)shell;
	if (!arguments[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (arguments[i] && check_flag(arguments[i]))
	{
		no_trailing_newline = true;
		i++;
	}
	while (arguments[i])
	{
		write_arg(arguments[i]);
		i++;
		if (arguments[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!no_trailing_newline)
		write(STDOUT_FILENO, "\n", 1);
}
