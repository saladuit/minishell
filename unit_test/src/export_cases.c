/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_cases.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:38:58 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:39:00 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

TestSuite(export, .init=redirect_all_std);

/*******************************************************************************/
/*                               Export_no_arg                                 */
/*******************************************************************************/

void	assert_export_no_arg(char **in, t_status expected_status)
{
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	ft_export(in, &shell);
	cr_assert_eq(shell.status, expected_status);
}

Test(export, no_argument)
{
	char	*in[] = {"export", NULL};
	assert_export_no_arg(in, E_USAGE);
}

/*******************************************************************************/
/*                               Export_cases                                  */
/*******************************************************************************/

void	assert_export(char **in, char *key, char *expected_value, t_status expected_status, char **environ)
{
	char		*expression;
	t_minishell	shell;

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_export(in, &shell);
	cr_assert_eq(shell.status, expected_status);
	expression = dict_get(&shell.env, key);
	cr_assert_str_eq(expression, expected_value);
}

Test(export, one_arg)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, one_arg_with_equal_sign_in_value)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=Hello=bye", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello=bye";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, two_args)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "ORANGE=Orange" , "BANANAS=Bananas", NULL};
	char	*key = "ORANGE";
	char	*expected_value = "Orange";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, two_args_test_the_second_one)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "ORANGE=Orange" , "BANANAS=Bananas", NULL};
	char	*key = "BANANAS";
	char	*expected_value = "Bananas";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, two_args_first_invalid_second_valid)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", "CHECK=check", NULL};
	char	*key = "CHECK";
	char	*expected_value = "check";
	assert_export(in, key, expected_value, E_GENERAL, environ);
}

Test(export, empty_value)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO", NULL};
	char	*key = "HELLO";
	char	*expected_value = "";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, empty_value_with_equal_sign)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=", NULL};
	char	*key = "HELLO";
	char	*expected_value = "";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

Test(export, existing_key_and_overwrite_value)
{
	char	*environ[] = {"HELLO=hoi", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello";
	assert_export(in, key, expected_value, E_USAGE, environ);
}
Test(export, overwrite_existing_key_with_equal_sign)
{
	char	*environ[] = {"HELLO=", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello";
	assert_export(in, key, expected_value, E_USAGE, environ);
}
Test(export, overwrite_existing_key_without_equal_sign)
{
	char	*environ[] = {"HELLO", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello";
	assert_export(in, key, expected_value, E_USAGE, environ);
}

/*******************************************************************************/
/*                           Export_invalid_cases                              */
/*******************************************************************************/

void	assert_export_not_valid_cases(char **in, t_status expected_status, char **environ, char *message)
{
	t_minishell	shell;
	(void)message;
	(void)expected_status;

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_export(in, &shell);
	fflush(stderr);
	cr_assert_eq(shell.status, expected_status);
	cr_expect_stderr_eq_str(message);
	dict_destroy(&shell.env);
}

Test(export, invalid_key)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", NULL};
	assert_export_not_valid_cases(in, E_GENERAL, environ, "Sheldon: export: `1234': not a valid identifier\n");
}

Test(export, two_invalid_keys)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", "5678", NULL};
	assert_export_not_valid_cases(in, E_GENERAL, environ, "Sheldon: export: `1234': not a valid identifier\nSheldon: export: `5678': not a valid identifier\n");
}

Test(export, invalid_with_equal_sign)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "=value", NULL};
	assert_export_not_valid_cases(in, E_GENERAL, environ, "Sheldon: export: `=value': not a valid identifier\n");
}

/*******************************************************************************/
/*                        Export_invalid_and_valid_case                        */
/*******************************************************************************/

Test(export, invalid_key_and_a_valid_key)
{
	t_minishell	shell;
	char		*expression;
	char		*environ[] = {"", NULL};
	char		*in[] = {"export", "1234", "check", NULL};

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_export(in, &shell);
	fflush(stderr);
	cr_assert_eq(shell.status, E_GENERAL);
	expression = dict_get(&shell.env, "check");
	cr_assert_str_eq(expression, "");
}

/*******************************************************************************/
/*                           Export_malloc_check                               */
/*******************************************************************************/

void	assert_export_malloc_check(char **in, t_status expected_status, char **environ)
{
	t_minishell	shell;
	int			condition;

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	set_malloc_failure_condition(0);
	ft_export(in, &shell);
	condition = get_malloc_failure_condition();
	dict_destroy(&shell.env);
	while (condition > 0)
	{
		bzero(&shell, sizeof(t_minishell));
		envp_load(&shell.env, environ);
		activate_malloc_hook();
		set_malloc_failure_condition(condition);
		ft_export(in, &shell);
		deactivate_malloc_hook();
		cr_assert_eq(shell.status, expected_status);
		dict_destroy(&shell.env);
		condition--;
	}
}

Test(export, malloc_check_one_arg)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	assert_export_malloc_check(in, E_GENERAL, environ);
}

Test(export, malloc_check_two_args)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "ORANGE=Orange" , "BANANAS=Bananas", NULL};
	assert_export_malloc_check(in, E_GENERAL, environ);
}

Test(export, malloc_check_invalid_arg)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", NULL};
	assert_export_malloc_check(in, E_GENERAL, environ);
}

Test(export, malloc_check_no_arg)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", NULL};
	assert_export_malloc_check(in, E_GENERAL, environ);
}
