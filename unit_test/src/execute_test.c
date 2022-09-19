#include <unit_test.h>
#include <unistd.h>

void	execute_test(const char *path, char **args, char **envp, const int32_t ret)
{
	int32_t	submitted;
	int32_t	status;
	pid_t	pid;

	(void)path;
	// submitted = 0;
	// submitted = execute;
	waitpid(execute, &status, WUNTRACED);
	// read(STDIN_FILENO, output, 1000);
	// close(ends[0]);
	// cr_log_info("%s\n", output);
	cr_assert(ret == WEXITSTATUS(status), "%d",WEXITSTATUS(status));
	return ;
}
