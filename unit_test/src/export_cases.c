#include <unit_test.h>

/*******************************************************************************/
/*                               Export_no_arg                                 */
/*******************************************************************************/

void	assert_export_no_arg(char **in, t_status expected_status)
{
	t_minishell	shell;
	bzero(&shell, sizeof(t_minishell));

	ft_export(in, NULL);
	cr_assert_eq(shell.status, expected_status);
}

Test(export, no_argument)
{
	char	*in[] = {"export", NULL};
	assert_export_no_arg(in, 0);
}

/*******************************************************************************/
/*                               Export_cases                                  */
/*******************************************************************************/

//TestSuite(export, .init=redirect_all_std);

void	assert_export(char **in, char *key, char *expected_value, t_status expected_status, char **environ)
{
	char		*expression;
	t_minishell	shell;

	fflush(stdout);
	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_export(in, &shell);
	cr_assert_eq(shell.status, expected_status);
	expression = dict_get(&shell.env, key);
	cr_assert_str_eq(expression, expected_value);
}

Test(export, export_one)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=Hello", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello";
	assert_export(in, key, expected_value, 0, environ);
}

Test(export, export_one_equal_sign_and_another)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=Hello=bye", NULL};
	char	*key = "HELLO";
	char	*expected_value = "Hello=bye";
	assert_export(in, key, expected_value, 0, environ);
}

Test(export, export_two_test_one)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "ORANGE=Orange" , "BANANAS=Bananas", NULL};
	char	*key = "ORANGE";
	char	*expected_value = "Orange";
	assert_export(in, key, expected_value, 0, environ);
}

Test(export, export_two_test_two)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "ORANGE=Orange" , "BANANAS=Bananas", NULL};
	char	*key = "BANANAS";
	char	*expected_value = "Bananas";
	assert_export(in, key, expected_value, 0, environ);
}

Test(export, export_not_valid_with_valid)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", "CHECK=check", NULL};
	char	*key = "CHECK";
	char	*expected_value = "check";
	assert_export(in, key, expected_value, 1, environ);
}

Test(export, export_one_empty)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO", NULL};
	char	*key = "HELLO";
	char	*expected_value = "";
	assert_export(in, key, expected_value, 0, environ);
}

Test(export, export_one_empty_with_equal_sign)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "HELLO=", NULL};
	char	*key = "HELLO";
	char	*expected_value = "";
	assert_export(in, key, expected_value, 0, environ);
}

/*******************************************************************************/
/*                          Export_not_valid_cases                             */
/*******************************************************************************/

TestSuite(export, .init=redirect_all_std);

void	assert_export_not_valid_cases(char **in, t_status expected_status, char **environ, char *message)
{
	t_minishell	shell;
	(void)message;
	(void)expected_status;

	fflush(stderr);
	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_export(in, &shell);
	cr_assert_eq(shell.status, expected_status);
	cr_expect_stderr_eq_str(message);
}

Test(export, not_a_valid_identifier_one)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", NULL};
	assert_export_not_valid_cases(in, 1, environ, "Sheldon: export: `1234': not a valid identifier\n");
}

Test(export, not_a_valid_identifier_two)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", "5678", NULL};
	assert_export_not_valid_cases(in, 1, environ, "Sheldon: export: `1234': not a valid identifier\nSheldon: export: `5678': not a valid identifier\n");
}

Test(export, not_a_valid_identifier_with_valid_arg)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "1234", "check", NULL};
	assert_export_not_valid_cases(in, 1, environ, "Sheldon: export: `1234': not a valid identifier\n");
}

Test(export, not_a_valid_with_equal_sign)
{
	char	*environ[] = {"", NULL};
	char	*in[] = {"export", "=value", NULL};
	assert_export_not_valid_cases(in, 1, environ, "Sheldon: export: `=value': not a valid identifier\n");
}
