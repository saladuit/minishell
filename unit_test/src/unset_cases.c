#include <unit_test.h>

/*******************************************************************************/
/*                              unset_cases                                    */
/*******************************************************************************/

void	assert_unset_cases(char **environ, char **in, char *expected, char *key)
{
	t_minishell	shell;
	char		*expression;

	bzero(&shell, sizeof(t_minishell));
	envp_load(&shell.env, environ);
	ft_unset(in, &shell);
	expression = dict_get(&shell.env, key);
	if (!expected)
		cr_assert_null(expression);
	else
		cr_assert_str_eq(expression, expected, "The expression: \'%s\' == expected: \'%s\' is false.\n", expression, expected);
	dict_destroy(&shell.env);
}

Test(unset, no_arg)
{
	char	*environ[] = {"A=aa", NULL};
	char	*in[] = {"unset", NULL};
	char	*expected = "aa";
	assert_unset_cases(environ, in, expected, "A");
}

Test(unset, one_arg)
{
	char	*environ[] = {"A=a", NULL};
	char	*in[] = {"unset", "A", NULL};
	char	*expected = NULL;
	assert_unset_cases(environ, in, expected, "A");
}

Test(unset, one_arg_two_in_env)
{
	char	*environ[] = {"A=a\nB=b\n", NULL};
	char	*in[] = {"unset", "B", NULL};
	char	*expected = NULL;
	assert_unset_cases(environ, in, expected, "B");
}


Test(unset, arg_with_value_is_numeric)
{
char	*environ[] = {"NUMERIC=1234\n", NULL};
char	*in[] = {"unset", "NUMERIC", NULL};
char	*expected = NULL;
assert_unset_cases(environ, in, expected, "NUMERIC");
}

Test(unset, arg_with_value_is_special_chars)
{
char	*environ[] = {"SPECIAL_CHARS=#@$", NULL};
char	*in[] = {"unset", "SPECIAL_CHARS", NULL};
char	*expected = NULL;
assert_unset_cases(environ, in, expected, "SPECIAL_CHARS");
}

Test(unset, two_args)
{
	char	*environ[] = {"A=a\nB=b\n", NULL};
	char	*in[] = {"unset", "A", "B", NULL};
	char	*expected = NULL;
	assert_unset_cases(environ, in, expected, "A");
	assert_unset_cases(environ, in, expected, "B");
}

Test(unset, two_keys_with_the_same_index)
{
	char	*environ[] = {"A=A\na=a\n", NULL};
	char	*in[] = {"unset", "A", "a", NULL};
	char	*expected = NULL;
	assert_unset_cases(environ, in, expected, "A");
	assert_unset_cases(environ, in, expected, "a");
}

Test(unset, three_args)
{
	char	*environ[] = {"A=a\nB=b\nCCC=ccc\n", NULL};
	char	*in[] = {"unset", "A", "B", "CCC", NULL};
	char	*expected = NULL;
	assert_unset_cases(environ, in, expected, "A");
	assert_unset_cases(environ, in, expected, "B");
	assert_unset_cases(environ, in, expected, "CCC");
}
