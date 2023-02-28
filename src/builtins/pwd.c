#include <minishell.h>

int	ft_pwd(char **arguments, t_minishell *shell)
{
	char	*buf;

	(void)arguments;
	(void)shell;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		return (errno);
	buf = ft_strjoin_free(buf, "\n");
	write(1, buf, ft_strlen(buf));
	free(buf);
	return (0);
}
