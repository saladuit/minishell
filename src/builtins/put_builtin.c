#include <minishell.h>

void put_builtin(const char *string, int fd)
{
	assert(write(fd, string, ft_strlen(string)) != ERROR);
}
