/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 16:52:43 by safoh         #+#    #+#                 */
/*   Updated: 2022/10/10 13:05:32 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1)
		ft_minishell_exit(USAGE);
	return (ft_minishell_exit(minishell(envp)));
}
