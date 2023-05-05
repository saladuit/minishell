/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safoh <safoh@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:39:06 by safoh             #+#    #+#             */
/*   Updated: 2023/05/04 11:39:11 by safoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		write(STDERR_FILENO, (char *)message_lookup(E_USAGE), 7);
		if (argv)
			ft_putendl_fd(*argv, STDERR_FILENO);
		else
			ft_putendl_fd("sheldon", STDERR_FILENO);
		exit(E_USAGE);
	}
	return (minishell(envp));
}
