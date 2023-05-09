/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_cases.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:39:24 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:39:26 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                               pwd_cases                                     */
/*******************************************************************************/

TestSuite(pwd, .init=redirect_all_std);

void	assert_pwd_cases(char **in, t_status expected_status)
{
	char		*cwd;
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	cwd = realpath(".", NULL);
	if (!cwd)
		return ;
	cwd = ft_strjoin_free(cwd, "\n");
	ft_pwd(in, &shell);
	fflush(stdout);
	cr_assert_stdout_eq_str(cwd);
	cr_assert_eq(shell.status, expected_status);
	free(cwd);
}

Test(pwd, no_arg)
{
	char	*in[] = {"pwd", NULL};
	assert_pwd_cases(in, E_USAGE);
}

Test(pwd, one_arg)
{
	char	*in[] = {"pwd", "one", NULL};
	assert_pwd_cases(in, E_USAGE);
}

Test(pwd, two_args)
{
	char	*in[] = {"pwd", "1", "2", NULL};
	assert_pwd_cases(in, E_USAGE);
}

/*******************************************************************************/
/*                            pwd_malloc_check                                 */
/*******************************************************************************/

void	assert_pwd_malloc_check(char **in, t_status expected_status)
{
	int condition;
	t_minishell	shell;

	(void)expected_status;
	bzero(&shell, sizeof(t_minishell));
	set_malloc_failure_condition(0);
	ft_pwd(in, &shell);
	condition = get_malloc_failure_condition();
	activate_malloc_hook();
	set_malloc_failure_condition(condition);
	deactivate_malloc_hook();
}

Test(pwd, malloc_check_no_arg)
{
	char	*in[] = {"pwd", NULL};
	assert_pwd_malloc_check(in, E_GENERAL);
}

/*******************************************************************************/
/*                            pwd_getcwd_fails                                 */
/*******************************************************************************/

void	assert_pwd_getcwd_fails(t_status expected_status)
{
	t_minishell shell;

	(void)expected_status;
	bzero(&shell, sizeof(t_minishell));
	ft_pwd(NULL, &shell);
	cr_assert_eq(shell.status, expected_status);
}

Test(pwd, getcwd_fails)
{
	assert_pwd_getcwd_fails(E_GENERAL);
}
