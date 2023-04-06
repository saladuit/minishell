#include <unit_test.h>

/*******************************************************************************/
/*                                   Exit                                      */
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

Test(exit, input_abc)
{
	char	*in[] = {"exit", "abc", NULL};
	assert_exit(in, true, 255);
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

Test(exit, input_256)
{
	char	*in[] = {"exit", "256", NULL};
	assert_exit(in, true, 0);
}