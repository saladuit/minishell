#include <message.h>

int32_t	ft_minishell_exit(t_message code)
{
	if (code == SUCCESS)
		exit(EXIT_SUCCESS);
	ft_putendl_fd((char *)messages_lookup(code), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

const char	*messages_lookup(t_message code)
{
	const char	*message[] = {
	[USAGE] = "Usage: ./minishell",
	[PROMPT] = "Minishell$ ",
	[EMALLOC] = "Malloc failed",
	[EREQUEST] = "Malloc failed",
	[ETYPE] = "Invalid type",
	};

	return (message[code]);
}
