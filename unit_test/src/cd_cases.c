#include <unit_test.h>

/*******************************************************************************/
/*                                 cd_home                                     */
/*******************************************************************************/

Test(cd, no_arg_with_home)
{
	t_minishell	shell;
	char	*environ[] = {"HOME=/tmp/cd-no_arg_with_home", NULL};
	char	*in[] = {"cd", NULL};

	system("mkdir /tmp/cd-no_arg_with_home");
	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_cd(in, &shell);
	cr_assert_eq(shell.status, E_USAGE);
	system("rmdir /tmp/cd-no_arg_with_home");
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
	cr_assert_not_null(&shell.env);
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
	dict_destroy(&shell.env);
}

Test(cd, relative_path_one_step)
{
	char	*in[] = {"cd", "build", NULL};
	assert_cd_relative_path(in, E_USAGE);
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
	dict_destroy(&shell.env);
}

Test(cd, absolute_path)
{
	char	*in[] = {"cd", "/tmp", NULL};
	assert_cd_absolute_path(in, E_USAGE);
}

Test(cd, absolute_path_invalid_folder)
{
	char	*in[] = {"cd", "/invalid_folder", NULL};
	assert_cd_absolute_path(in, E_BUILTIN);
}

/*******************************************************************************/
/*                                 cd_malloc                                   */
/*******************************************************************************/

Test(cd, malloc_check_no_arg)
{
	int 		condition;
	t_minishell	shell;
	char		*in[] = {"cd", "/tmp", NULL};
	char 		*environ[] = {NULL};

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	set_malloc_failure_condition(0);
	ft_cd(in, &shell);
	condition = get_malloc_failure_condition();
	dict_destroy(&shell.env);
	while (condition > 0)
	{
		bzero(&shell, sizeof(t_minishell));
		envp_load(&shell.env, environ);
		activate_malloc_hook();
		set_malloc_failure_condition(condition);
		ft_cd(in, &shell);
		deactivate_malloc_hook();
		cr_assert_eq(shell.status, E_GENERAL, "status: %d expected status: %d condition: %d", shell.status, E_GENERAL, condition);
		dict_destroy(&shell.env);
		condition--;
	}
}
