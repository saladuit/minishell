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

void	ft_echo(char **arguments, t_minishell *shell)
{
	size_t	i;
	bool	newline;

	(void)shell;
	newline = true;
	i = 1;
	while (arguments[i])
	{
		if (arguments[i] && !ft_strncmp(arguments[i], "-n", 2))
		{
			newline = false;
			i++;
			continue ;
		}
		write(STDOUT_FILENO, arguments[i], ft_strlen(arguments[i]));
		i++;
		if (arguments[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
