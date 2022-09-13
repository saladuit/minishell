/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minishell.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:44:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 17:07:58 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	minishell(char **envp)
{
	t_tree	*command_table;
	t_list	*tokens;

	command_table = NULL;
	tokens = NULL;
	while (true)
	{
		readline(messages_lookup(PROMPT));
		if (lexer(envp, &tokens) == ERROR)
			return (EXIT_FAILURE);
		if (parser(tokens, &command_table) == ERROR)
			return (EXIT_FAILURE);
		if (expander(command_table) == ERROR)
			return (EXIT_FAILURE);
		if (executor(command_table) == ERROR)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}
