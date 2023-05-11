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

static void	write_arg_and_set_flag(char **arguments, size_t *i,
									bool *still_flags)
{
	write(STDOUT_FILENO, arguments[*i], ft_strlen(arguments[*i]));
	if (arguments[++*i])
		write(STDOUT_FILENO, " ", 1);
	*still_flags = false;
}

void	ft_echo(char **arguments, t_minishell *shell)
{
	size_t	i;
	bool	newline;
	bool	still_flags;

	(void)shell;
	newline = true;
	i = 1;
	still_flags = true;
	while (arguments[i])
	{
		if (still_flags && arguments[i] && !ft_strncmp(arguments[i], "-n", 2))
		{
			newline = false;
			i++;
			continue ;
		}
		if (ft_strlen(arguments[i]) == 0)
		{
			i++;
			continue ;
		}
		write_arg_and_set_flag(arguments, &i, &still_flags);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
