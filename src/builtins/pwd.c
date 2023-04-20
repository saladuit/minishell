#include <minishell.h>

int	ft_pwd(char **arguments, t_minishell *shell)
{
	char	*buf;

	buf = NULL;
	if (arguments)
		buf = getcwd(buf, 0);
	if (buf == NULL)
	{
		shell->status = E_GENERAL;
		ft_putendl_fd("pwd: error: getcwd fails\n", STDERR_FILENO);
		return (1);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	free(buf);
	shell->status = E_USAGE;
	return (0);
}
