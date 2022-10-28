/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.h                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:56:37 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/10/28 12:32:10 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# define ERROR -1

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

typedef enum e_message
{
	SUCCESS,
	USAGE,
	PROMPT,
	EMALLOC,
	EREQUEST,
	ETYPE,
}	t_message;

const char	*messages_lookup(t_message code);
int32_t		ft_minishell_exit(t_message code);

#endif
