/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.h                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:56:37 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/12/02 14:52:20 by safoh        \___)=(___/                 */
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
/*
E_GENERAL: 
	Miscellaneous errors, such as "divide by zero" and other 
	impermissible operations,
E_BUILTIN:
	Missing keyword or command, or permission problem 
	(and diff return code on a failed binary file comparison).
E_EXEC:
	Permission problem or command is not an executable
E_COMMAND_NOT_FOUND:
	Possible problem with $PATH or a typo
E_EXIT_INVALID_ARG:
	exit takes only integer args in the range 0 - 255
E_FATAL_SIGNAL:
	$? returns 137 (128 + 9)
E_CTRL_C:
	Control-C is fatal error signal 2, (130 = 128 + 2, see above)
E_EXIT_STATUS_OUT_OF_RANGE:
	exit takes only integer args in the range 0 - 255
*/
typedef enum e_exitcodes
{
	E_GENERAL = 1,
	E_BUILTIN = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_EXIT_STATUS_OUT_OF_RANGE = 225
}	t_exitcodes;

const char	*messages_lookup(t_message code);
int32_t		ft_minishell_exit(t_message code);

#endif
