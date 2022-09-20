#include <unit_test.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//void	execute_test(const char *path, char **args, char **envp, const int32_t ret)
//{
//	int32_t	status;
//
//	(void)path;
//	waitpid(execute(args, envp), &status, WUNTRACED);
//	status = WEXITSTATUS(status);
//	cr_assert(ret == status, "%s", strerror(status));
//	return ;
//}
