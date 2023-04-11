#include <unit_test.h>

void redirect_all_std_for_exit(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

TestSuite(exit, .init=redirect_all_std_for_exit);

/*******************************************************************************/
/*                                Exit_cases                                   */
/*******************************************************************************/

void	assert_exit(char **in, bool expected_stop, t_status expected_status)
{
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	ft_exit(in, &shell);
	cr_expect_eq(shell.stop, expected_stop);
	cr_expect_eq(shell.status, expected_status, "The expression (shell.status): %d == (expected_status):  %d is false)", shell.status, expected_status);
}

Test(exit, no_argument)
{
	char	*in[] = {"exit", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_123)
{
	char	*in[] = {"exit", "123", NULL};
	assert_exit(in, true, 123);
}

Test(exit, input_2147483647)
{
	char	*in[] = {"exit", "2147483647", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_2147483646)
{
	char	*in[] = {"exit", "2147483646", NULL};
	assert_exit(in, true, 254);
}

Test(exit, input_2147483648)
{
	char	*in[] = {"exit", "2147483648", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_2147483649)
{
	char	*in[] = {"exit", "2147483649", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_2147483650)
{
	char	*in[] = {"exit", "2147483650", NULL};
	assert_exit(in, true, 2);
}

Test(exit, input_minus_21474836500000)
{
	char	*in[] = {"exit", "-21474836500000", NULL};
	assert_exit(in, true, 224);
}

Test(exit, input_21474836500000)
{
	char	*in[] = {"exit", "214748365000", NULL};
	assert_exit(in, true, 200);
}

Test(exit, input_256)
{
	char	*in[] = {"exit", "256", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_fence)
{
	char	*in[] = {"exit", "#", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_semicolon)
{
	char	*in[] = {"exit", ";", NULL};
	assert_exit(in, true, 0);
}

/*******************************************************************************/
/*                       Exit_cases_with_error_message                         */
/*******************************************************************************/

//char	*get_stderr_message(FILE *stderr_msg)
//{
//	char	*error_message = NULL;
//	size_t	error_size = 0;
//	size_t	read_size;
//
//	/* Read the error message from stderr_msg */
//	while ((read_size = fread(NULL, 1, 0, stderr_msg)) == 0)
//	{
//		error_message = realloc(error_message, error_size + BUFSIZ);
//		read_size = fread(error_message + error_size, 1, BUFSIZ, stderr_msg);
//		error_size += read_size;
//	}
//
//	/* Null-terminate the error message */
//	error_message = realloc(error_message, error_size + 1);
//	error_message[error_size] = '\0';
//
//	return error_message;
//}

void	assert_exit_error(char **in, bool expected_stop, t_status expected_status, char *expected_message)
{
	t_minishell	shell;
//	char		*err_msg;

	bzero(&shell, sizeof(t_minishell));
	fflush(stderr);
	ft_exit(in, &shell);
	cr_expect_eq(shell.stop, expected_stop);
	cr_expect_eq(shell.status, expected_status, "The expression (shell.status): %d == (expected_status):  %d is false)", shell.status, expected_status);
//	err_msg = get_stderr_message(stderr);
//	cr_expect_stderr_eq_str(expected_message, "actual: \"%s\", expected: \"%s\"\n", err_msg, expected_message);
	cr_expect_stderr_eq_str(expected_message);
}

Test(exit, input_alphabetical)
{
	char	*in[] = {"exit", "abc", NULL};
	assert_exit_error(in, true, 255, "Sheldon: exit: abc: numeric argument required\n");
}

Test(exit, input_at_sign)
{
	char	*in[] = {"exit", "@", NULL};
	assert_exit_error(in, true, 255, "Sheldon: exit: @: numeric argument required\n");
}

Test(exit, input_exclamation_mark)
{
	char	*in[] = {"exit", "!", NULL};
	assert_exit_error(in, true, 255, "Sheldon: exit: !: numeric argument required\n");
}

/*******************************************************************************/
/*                            Exit_cases_is_pipeline                           */
/*******************************************************************************/

void	assert_exit_is_pipeline(char **in, t_status expected_status)
{
	t_minishell	shell;
	pid_t		child;

	bzero(&shell, sizeof(t_minishell));
	shell.is_pipeline = true;
	child = fork();
	if (child == -1) {
		perror("fork");
		exit(1);
	}
	else if (child == 0)
	{
		ft_exit(in, &shell);
	}
	else
	{
		waitpid(child, (int *) &shell.status, 0);
		cr_expect_eq(WEXITSTATUS(shell.status), expected_status, "The expression (shell.status): %d == (expected_status):  %d is false)", WEXITSTATUS(shell.status), expected_status);
	}
}

Test(exit, input_child_zero)
{
	char	*in[] = {"exit", "0", NULL};
	assert_exit_is_pipeline(in, 0);
}

Test(exit, input_child_one)
{
	char	*in[] = {"exit", "1", NULL};
	assert_exit_is_pipeline(in, 1);
}

Test(exit, input_child_big_number)
{
	char	*in[] = {"exit", "999", NULL};
	assert_exit_is_pipeline(in, 231);
}
