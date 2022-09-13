/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.h                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:56:37 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 16:07:14 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

typedef enum e_message
{
	SUCCESS,
	PROMPT,
	EINPUT,
	EMALLOC,
}	t_message;

const char	*messages_lookup(t_message code);
int32_t		ft_minishell_exit(t_message code);

#endif
