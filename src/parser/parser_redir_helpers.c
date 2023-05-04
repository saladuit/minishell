/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser_redir_helpers.c                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 19:01:33 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 19:01:33 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	handle_redir(t_list **tokens, t_command *command)
{
	t_redir	*redir;

	redir = construct_redir(tokens);
	if (!redir || !ft_lstadd_backnew(&command->redirs, redir))
	{
		deconstruct_redirs(redir);
		return (ERROR);
	}
	command->n_redirs++;
	return (SUCCESS);
}

t_type	set_type(char *symbol, size_t len)
{
	if (!ft_strncmp("<", symbol, len))
		return (INPUT);
	else if (!ft_strncmp("<<", symbol, len))
		return (HEREDOC);
	else if (!ft_strncmp(">", symbol, len))
		return (OUTPUT);
	return (APPEND);
}
