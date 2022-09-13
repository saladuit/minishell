/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   main.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/03/21 16:52:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 16:00:56 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		exit(EXIT_SUCCESS);
	return (ft_minishell_exit(minishell(argv, envp)));
}
