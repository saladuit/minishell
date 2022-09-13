/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minshell.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:44:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 15:51:38 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

int32_t	minishell(char *argv, char **envp)
{
	if (lexer(argv, envp) == ERROR)
		return (ELEXER);
//	if (parser(argv, envp) == ERROR)
//		return (ELEXER);
//	if (executor(argv, envp) == ERROR)
//		return (ELEXER);
//	if (e(argv, envp) == ERROR)
//		return (ELEXER);
	readline("Minishell$ ");
	return (EXIT_SUCCESS);
}
