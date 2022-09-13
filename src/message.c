/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   message.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 15:52:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 16:05:08 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */


int32_t	ft_minishell_exit(t_message code)
{
	if (code == SUCCESS)
		 exit(EXIT_SUCCESS);
	ft_error();
	ft_putendl_fd(messages_lookup(code), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

const char	*messages_lookup(t_message code)
{
	const char	*message[] = {
	[PROMPT] = "./minishell$",
	[EINPUT] = "Invalid input",
	[EMALLOC] = "Malloc failed",
	};

	return (message[code]);
}
