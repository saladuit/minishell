#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <libft.h>

int ft_pwd(char **arguments, char **envp)
{
	char	*buf;

	(void)arguments;
	(void)envp;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		return (errno);
	buf = ft_strjoin_free(buf, "\n");
	write(1, buf, ft_strlen(buf));
	free(buf);
	return (0);
}
