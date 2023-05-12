#include <unit_test.h>

/*******************************************************************************/
/*                               Env_cases                                     */
/*******************************************************************************/

void assert_env(char **input, char *expected, char **environ)
{
	t_minishell	shell;

	bzero(&shell, sizeof(shell));
	envp_load(&shell.env, environ);
	ft_env(input, &shell);
	cr_assert_not_null(expected);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
	dict_destroy(&shell.env);
}

Test(env_builtin, empty, .init=redirect_stdout)
{
	char	*environ[] = {"", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "";
	assert_env(input, expected, environ);
}

Test(env_builtin, non_existent_key, .init=redirect_stdout)
{
	char	*environ[] = {"", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "";
	assert_env(input, expected, environ);
}

Test(env_builtin, only_value_is_empty, .init=redirect_stdout)
{
	char	*environ[] = {"EMPTY=", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "EMPTY=\n";
	assert_env(input, expected, environ);
	}

Test(env_builtin, key_and_value, .init=redirect_stdout)
{
	char	*environ[] = {"HELLO=Hello", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "HELLO=Hello\n";
	assert_env(input, expected, environ);
}

Test(env_builtin, two_keys_with_value, .init=redirect_stdout)
{
	char	*environ[] = {"HELLO=Hello\nBYE=Bye", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "HELLO=Hello\nBYE=Bye\n";
	assert_env(input, expected, environ);
}

/*******************************************************************************/
/*                            Env_multiple_args                                */
/*******************************************************************************/

void	assert_env_multiple_args(char **input, int expected)
{
	t_minishell	shell;

	bzero(&shell, sizeof(shell));
	ft_env(input, &shell);
	int	expression = (int) shell.status;
	cr_assert_eq(expression, expected);
}

Test(env_builtin, arg_is_two)
{
	char	*input[] = {"env", "yes", NULL};
	int		expected = E_COMMAND_NOT_FOUND;
	assert_env_multiple_args(input, expected);
}

Test(env_builtin, arg_is_three)
{
	char	*input[] = {"env", "yes", "no", NULL};
	int		expected = E_COMMAND_NOT_FOUND;
	assert_env_multiple_args(input, expected);
}
