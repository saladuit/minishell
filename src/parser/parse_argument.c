/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parse_argument.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:34:53 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:34:53 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_arguments(t_command *cmd)
{
	char	**arguments;
	int32_t	i;

	arguments = get_arguments(cmd);
	i = 0;
	if (!arguments)
		return ;
	while (arguments[i])
	{
		printf("\t\tArgument #%d: %s\n", i + 1, arguments[i]);
		i++;
	}
	free(arguments);
}

char	**get_arguments(t_command *cmd)
{
	char	**arguments;
	int32_t	i;

	arguments = ft_calloc(cmd->n_arguments + 1, sizeof(char *));
	if (!arguments)
		return (NULL);
	i = 0;
	while (cmd->arguments)
	{
		arguments[i] = cmd->arguments->content;
		cmd->arguments = cmd->arguments->next;
		i++;
	}
	cmd->arguments = cmd->arguments_head;
	return (arguments);
}
