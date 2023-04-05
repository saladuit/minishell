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
	cr_expect_eq(shell.status, expected_status);

}

Test(exit, no_argument)
{
	char	*in[] = {"exit", NULL};
	assert_exit(in, true, 0);
}