#include <unit_test.h>

/*******************************************************************************/
/*                               Env_cases                                     */
/*******************************************************************************/

TestSuite(env_builtin, .init=redirect_all_std);

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

Test(env_builtin, empty)
{
	char	*environ[] = {"", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "";
	assert_env(input, expected, environ);
}

Test(env_builtin, empty_is_empty)
{
	char	*environ[] = {"EMPTY=", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "EMPTY=\n";
	assert_env(input, expected, environ);
	}

Test(env_builtin, hello)
{
	char	*environ[] = {"HELLO=Hello", NULL};
	char	*input[] = {"env", NULL};
	char	*expected = "HELLO=Hello\n";
	assert_env(input, expected, environ);
}

Test(env_builtin, hello_bye)
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
	int	expression = ft_env(input, &shell);
	cr_assert_eq(expression, expected);
}

Test(env_builtin, arg_is_two)
{
	char	*input[] = {"env", "yes", NULL};
	int		expected = 127;
	assert_env_multiple_args(input, expected);
}

Test(env_builtin, arg_is_three)
{
	char	*input[] = {"env", "yes", "no", NULL};
	int		expected = 127;
	assert_env_multiple_args(input, expected);
}