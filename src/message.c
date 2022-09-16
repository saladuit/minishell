/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:52:38 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 10:08:18 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <message.h>
#include <unistd.h>

int32_t	ft_minishell_exit(t_message code)
{
	if (code == SUCCESS)
		 exit(EXIT_SUCCESS);
	if (code == USAGE)
		ft_putendl_fd((char *)messages_lookup(code), STDOUT_FILENO);
	else
	{
		ft_error();
		ft_putendl_fd((char *)messages_lookup(code), STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}

const char	*messages_lookup(t_message code)
{
	const char	*message[] = {
	[USAGE] = "Usage: ./minishell",
	[PROMPT] = "Minishell$ ",
	[EMALLOC] = "Malloc failed",
	};

	return (message[code]);
}
