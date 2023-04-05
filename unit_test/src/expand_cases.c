#include <unit_test.h>

t_status zero = 0;
t_status max = 255;
extern char	**environ;

void setup_env(void)
{
    setenv("HELLO", "Hello", 1);
    setenv("WORLD", "World", 1);
    unsetenv("UNSET");
    setenv("SPACE", "Spa ce", 1);
	setenv("VAR", "b c d", 1);
	setenv("EMPTY", "", 1);
	setenv("A", "b c d", 1);
	setenv("B", "e f g", 1);
}

/*******************************************************************************/
/*                           Expand_token                                      */
/*******************************************************************************/

char *expand_token(char *arg, t_status *status, t_dictionary *envd);

TestSuite(expand_token, .init=setup_env);

void assert_expand_token(char *in, char *expected, t_status *status)
{
	t_dictionary env[HASH_TABLE_SIZE];

	bzero(env, sizeof(env));
	envp_load(env, environ);
//	dict_print(env);
    char *input;
    input = ft_strdup(in);
    char *output = expand_token(input, status, env);
    cr_expect_str_eq(output, expected, "The expression (as strings) (output) == (expected) is false: actual=`%s` expected=%s` input='%s'",output, expected, in);
    free(output);
    free(input);
	dict_destroy(env);
}

/*******************************************************************************/
/*                           Basic_test_cases                                  */
/*******************************************************************************/

Test(expand_token, envvar_not_set)
{
	assert_expand_token("$UNSET", "", NULL);
}

Test(expand_token, null_null, .signal=SIGABRT)
{
	expand_token(NULL, NULL, NULL);
}

Test(expand_token, empty)
{
	assert_expand_token("", "", NULL);
}

Test(expand_token, string)
{
	assert_expand_token("Hello", "Hello", NULL);
}

Test(expand_token, envvar_single)
{
	assert_expand_token("$HELLO", "Hello", NULL);
}

Test(expand_token, exit_status)
{
    assert_expand_token("$?", "0", &zero);
}

Test(expand_token, exit_status_max)
{
    assert_expand_token("$?", "255", &max);
}

Test(expand_token, echo_shell_in_double_quotes)
{
	assert_expand_token("\"$HELLO\"", "Hello", NULL);
}

Test(expand_token, echo_shell_in_single_quotes)
{
	assert_expand_token("\'$HELLO\'", "$HELLO", NULL);
}

Test(expand_token, envvar_dollar)
{
    assert_expand_token("$", "$", NULL);
}

Test(expand_token, envvar_double_dollar)
{
	assert_expand_token("$$", "", NULL);
}

Test(expand_token, string_twice)
{
	assert_expand_token("HelloHello", "HelloHello", NULL);
}

Test(expand_token, envvar_single_twice)
{
	assert_expand_token("$HELLO$HELLO", "HelloHello", NULL);
}

Test(expand_token, exit_status_twice)
{
	assert_expand_token("$?$?", "00", &zero);
}

Test(expand_token, exit_status_max_twice)
{
	assert_expand_token("$?$?", "255255", &max);
}

Test(expand_token, echo_shell_in_double_quotes_twice)
{
	assert_expand_token("\"$HELLO\"\"$HELLO\"", "HelloHello", NULL);
}

Test(expand_token, echo_shell_in_single_quotes_twice)
{
	assert_expand_token("\'$HELLO\'\'$HELLO\'", "$HELLO$HELLO", NULL);
}

Test(expand_token, envvar_double_dollar_twice)
{
	assert_expand_token("$$$$", "", NULL);
}

Test(expand_token, string_twice_with_space)
{
	assert_expand_token("Hello Hello", "Hello Hello", NULL);
}

Test(expand_token, envvar_single_twice_with_space)
{
	assert_expand_token("$HELLO $HELLO", "Hello Hello", NULL);
}

Test(expand_token, exit_status_twice_with_space)
{
	assert_expand_token("$? $?", "0 0", &zero);
}

Test(expand_token, exit_status_max_twice_with_space)
{
	assert_expand_token("$? $?", "255 255", &max);
}

Test(expand_token, echo_shell_in_double_quotes_twice_with_space)
{
	assert_expand_token("\"$HELLO\" \"$HELLO\"", "Hello Hello", NULL);
}

Test(expand_token, echo_shell_in_single_quotes_twice_with_space)
{
	assert_expand_token("\'$HELLO\' \'$HELLO\'", "$HELLO $HELLO", NULL);
}

Test(expand_token, envvar_dollar_twice_with_space)
{
	assert_expand_token("$ $", "$ $", NULL);
}

Test(expand_token, envvar_double_dollar_twice_with_space)
{
	assert_expand_token("$$ $$", " ", NULL);
}

Test(expand_token, all_basic_cases_together)
{
	assert_expand_token("HELLO$HELLO\"$HELLO\"\'$HELLO\'$$$$?", "HELLOHelloHello$HELLO?", &zero);
}

/*******************************************************************************/
/*                           Random_test_cases                                 */
/*******************************************************************************/

Test(expand_token, envar_dollar_with_space_and_letter)
{
	assert_expand_token("$ a", "$ a", NULL);
}
Test(expand_token, envvar_double)
{
	assert_expand_token("$HELLO $?", "Hello 255", &max);
}

Test(expand_token, envvar_single_quotes)
{
    assert_expand_token("\'$VAR\'", "$VAR", NULL);
}

Test(expand_token, echo_shell_shell_ja)
{
	assert_expand_token("$HELLO$HELLOja", "Hello", NULL);
}

Test(expand_token, echo_shell_shell_ja_in_single_quotes)
{
	assert_expand_token("$HELLO$HELLO\'ja\'", "HelloHelloja", NULL);
}

Test(expand_token, echo_shell_shell_ja_in_double_quotes)
{
	assert_expand_token("$HELLO$HELLO\"ja\"", "HelloHelloja", NULL);
}

Test(expand_token, echo_abcdef)
{
	assert_expand_token("a$VAR\'ef\'", "ab c def", NULL);
}

Test(expand_token, echo_abcdef_empty_input)
{
	assert_expand_token("a$EMPTY\'ef\'", "aef", NULL);
}

Test(expand_token, echo_a_and_b)
{
	assert_expand_token("a$A$B\"h\"", "ab c de f gh", NULL);
}

Test(expand_token, echo_shell_single_and_double_quotes)
{
	assert_expand_token("\'$HELLO\'\"$HELLO\"",  "$HELLOHello", NULL);
}

Test(expand_token, echo_shell_shell_quotes)
{
	assert_expand_token("$HELLO$HELLO\'\'", "HelloHello", NULL);
}

Test(expand_token, echo_empty_input)
{
	assert_expand_token("  $EMPTY", "  ", NULL);
}

Test(expand_token, envvar_single_quotes_1)
{
    assert_expand_token("\'$VAR\"\'", "$VAR\"", NULL);
}

Test(expand_token, envvar_single_quotes_2)
{
    assert_expand_token("\'$VAR$\'", "$VAR$", NULL);
}

Test(expand_token, double_quote_no_envvar)
{
    assert_expand_token("\"HELLO\"", "HELLO", NULL);
}


Test(expand_token, double_quote_envvar)
{
    assert_expand_token("\"$HELLO\"", "Hello", NULL);
}

Test(expand_token, double_quote_two_envvar)
{
    assert_expand_token("\"$HELLO$WORLD\"", "HelloWorld", NULL);
}

Test(expand_token, envvar_with_spaces)
{
    assert_expand_token("echo $SPACE", "echo Spa ce", NULL);
}

Test(expand_token, various_1)
{
    assert_expand_token("\"$? \'$?\' $?\"", "0 \'0\' 0", &zero);
}

Test(expand_token, various_2)
{
	assert_expand_token("$?\'$?\"\'\"$?\"", "0$?\"0", &zero);
}

Test(expand_token, various_3)
{
    assert_expand_token("\"$?\'$?\'\"$?\"\"", "0\'0\'0", &zero);
}

Test(expand_token, various_4)
{
    assert_expand_token("echo $SPACE", "echo Spa ce", NULL);
}
