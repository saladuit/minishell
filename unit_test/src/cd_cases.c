#include <unit_test.h>

/*******************************************************************************/
/*                                 cd_home                                     */
/*******************************************************************************/

// STILL FAILING
Test(cd, no_arg_with_home)
{
	t_minishell	shell;
	char *environ[] = {"HOME=/build/test", NULL};
	char	*in[] = {"cd", NULL};

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	system("mkdir build/test");
	ft_cd(in, &shell);
	cr_assert_eq(shell.status, E_USAGE);
	system("rmdir build/test");
	dict_destroy(&shell.env);
}

/*******************************************************************************/
/*                                 cd_home_unset                               */
/*******************************************************************************/

Test(cd, no_arg_with_home_unset)
{
	t_minishell	shell;
	char *environ[] = {NULL};
	char	*in[] = {"cd", NULL};

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_cd(in, &shell);
	cr_assert_eq(shell.status, E_BUILTIN);
	dict_destroy(&shell.env);
}

/*******************************************************************************/
/*                               cd_relative_path                              */
/*******************************************************************************/

void	assert_cd_relative_path(char **in, t_status expected_status)
{
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	ft_cd(in, &shell);
	cr_assert_eq(shell.status, expected_status);
}

Test(cd, relative_path_one_step)
{
	char	*in[] = {"cd", "build", NULL};
	assert_cd_relative_path(in, E_USAGE);
}

Test(cd, relative_path_two_steps)
{
	system("mkdir build/test");
	char	*in[] = {"cd", "build/test", NULL};
	assert_cd_relative_path(in, E_USAGE);
	system("rmdir build/test");
}

Test(cd, relative_path_one_step_back)
{
	char	*in[] = {"cd", "..", NULL};
	assert_cd_relative_path(in, E_USAGE);
}

Test(cd, relative_path_two_steps_back)
{
	char	*in[] = {"cd", "../..", NULL};
	assert_cd_relative_path(in, E_USAGE);
}

Test(cd, relative_path_arg_zero_is_a)
{
	char	*in[] = {"a", "../..", NULL};
	assert_cd_relative_path(in, E_BUILTIN);
}

Test(cd, relative_path_arg_zero_is_b)
{
	char	*in[] = {"b", "../..", NULL};
	assert_cd_relative_path(in, E_BUILTIN);
}

Test(cd, relative_path_not_existing)
{
	char	*in[] = {"cd", "not_existing", NULL};
	assert_cd_relative_path(in, E_BUILTIN);
}

/*******************************************************************************/
/*                               cd_absolute_path                              */
/*******************************************************************************/

void	assert_cd_absolute_path(char **in, t_status expected_status)
{
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	ft_cd(in, &shell);
	cr_assert_eq(shell.status, expected_status);
}

Test(cd, absolute_path_two_steps)
{
	char	*in[] = {"cd", "/Users/lvan-bus/desktop", NULL};
	assert_cd_absolute_path(in, E_USAGE);
}

Test(cd, absolute_path_one_step_invalid_folder)
{
	char	*in[] = {"cd", "/Users/lvan-bus/invalid_folder", NULL};
	assert_cd_absolute_path(in, E_BUILTIN);
}
