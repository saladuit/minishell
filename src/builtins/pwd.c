#include <minishell.h>

static void pwd_error_msg(void)
{
	ft_putstr_fd("pwd: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int	ft_pwd(char **arguments, t_minishell *shell)
{
	char	*buf;

	if (arguments)
		buf = getcwd(NULL, 0);
	else
		buf = NULL;
	if (buf == NULL)
	{
		shell->status = E_GENERAL;
		pwd_error_msg();
		return (1);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	free(buf);
	return (0);
}
