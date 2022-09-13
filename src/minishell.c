/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minshell.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:44:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 16:12:18 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	minishell(char *argv, char **envp)
{
	t_tree astree;

	astree = NULL;
	if (lexer(argv, envp, &astree) == ERROR)
		return (EXIT_FAILURE);
	if (parser(&astree) == ERROR)
		return (EXIT_FAILURE);
	if (expander(&astree) == ERROR)
		return (EXIT_FAILURE);
	if (executor(&astree) == ERROR)
		return (EXIT_FAILURE);
	readline("Minishell$ ");
	return (EXIT_SUCCESS);
}
