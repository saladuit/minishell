#include "message.h"
#include <unistd.h>
void	cd_builtin(const char *path)
{
	chdir(path);
//		ft_minishell_error(INVALID_PATH);
}

void	echo_builtin(const char *line)
{

}

void
