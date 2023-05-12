#include <unit_test.h>

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
	setenv("IFS", "IFS", 1);
	setenv("_", "", 1);

}

TestSuite(expand_token, .init=setup_env);


/*******************************************************************************/
/*                           Expand_token                                      */
/*******************************************************************************/

void assert_expand_token(const char *input, char *expected, t_status status)
{
	t_dictionary env[HASH_TABLE_SIZE];
	t_status local_status;
	int condition;
	char *output;

	local_status = status;
	bzero(env, sizeof(env));
	envp_load(env, environ);
	set_malloc_failure_condition(0);
	output = expand_token((char *)input, &local_status, env);
	cr_expect_str_eq(output, expected,
					 "The expression (as strings) (output) == (expected) is false: actual=`%s` expected=%s` input='%s'",
					 output, expected, input);
	free(output);
	condition = get_malloc_failure_condition();
	while (condition > 0)
	{
		activate_malloc_hook();
		set_malloc_failure_condition(condition);
		output = expand_token((char *)input, &local_status, env);
		deactivate_malloc_hook();
		cr_assert_null(output, "Expected test function to return NULL on malloc failure. condition: %d",condition);
		free(output);
		condition--;
	}
	dict_destroy(env);
}

/*******************************************************************************/
/*                           Basic_test_cases                                  */
/*******************************************************************************/

Test(expand_token, envvar_not_set)
{
	assert_expand_token("$UNSET", "", 0);
}

Test(expand_token, empty)
{
	assert_expand_token("", "", 0);
}

Test(expand_token, string)
{
	assert_expand_token("Hello", "Hello", 0);
}

Test(expand_token, envvar_single)
{
	assert_expand_token("$HELLO", "Hello", 0);
}

Test(expand_token, exit_status)
{
    assert_expand_token("$?", "0", 0);
}

Test(expand_token, exit_status_max)
{
    assert_expand_token("$?", "255", 255);
}

Test(expand_token, echo_shell_in_double_quotes)
{
	assert_expand_token("\"$HELLO\"", "Hello", 0);
}

Test(expand_token, echo_shell_in_single_quotes)
{
	assert_expand_token("\'$HELLO\'", "$HELLO", 0);
}

Test(expand_token, envvar_dollar)
{
    assert_expand_token("$", "$", 0);
}

Test(expand_token, envvar_double_dollar)
{
	assert_expand_token("$$", "", 0);
}

Test(expand_token, string_twice)
{
	assert_expand_token("HelloHello", "HelloHello", 0);
}

Test(expand_token, envvar_single_twice)
{
	assert_expand_token("$HELLO$HELLO", "HelloHello", 0);
}

Test(expand_token, exit_status_twice)
{
	assert_expand_token("$?$?", "00", 0);
}

Test(expand_token, exit_status_max_twice)
{
	assert_expand_token("$?$?", "255255", 255);
}

Test(expand_token, echo_shell_in_double_quotes_twice)
{
	assert_expand_token("\"$HELLO\"\"$HELLO\"", "HelloHello", 0);
}

Test(expand_token, echo_shell_in_single_quotes_twice)
{
	assert_expand_token("\'$HELLO\'\'$HELLO\'", "$HELLO$HELLO", 0);
}

Test(expand_token, envvar_double_dollar_twice)
{
	assert_expand_token("$$$$", "", 0);
}

Test(expand_token, string_twice_with_space)
{
	assert_expand_token("Hello Hello", "Hello Hello", 0);
}

Test(expand_token, envvar_single_twice_with_space)
{
	assert_expand_token("$HELLO $HELLO", "Hello Hello", 0);
}

Test(expand_token, exit_status_twice_with_space)
{
	assert_expand_token("$? $?", "0 0", 0);
}

Test(expand_token, exit_status_max_twice_with_space)
{
	assert_expand_token("$? $?", "255 255", 255);
}

Test(expand_token, echo_shell_in_double_quotes_twice_with_space)
{
	assert_expand_token("\"$HELLO\" \"$HELLO\"", "Hello Hello", 0);
}

Test(expand_token, echo_shell_in_single_quotes_twice_with_space)
{
	assert_expand_token("\'$HELLO\' \'$HELLO\'", "$HELLO $HELLO", 0);
}

Test(expand_token, envvar_dollar_twice_with_space)
{
	assert_expand_token("$ $", "$ $", 0);
}

Test(expand_token, envvar_double_dollar_twice_with_space)
{
	assert_expand_token("$$ $$", " ", 0);
}

Test(expand_token, all_basic_cases_together)
{
	assert_expand_token("HELLO$HELLO\"$HELLO\"\'$HELLO\'$$$$?", "HELLOHelloHello$HELLO?", 0);
}

/*******************************************************************************/
/*                           Random_test_cases                                 */
/*******************************************************************************/

Test(expand_token, envar_dollar_with_space_and_letter)
{
	assert_expand_token("$ a", "$ a", 0);
}
Test(expand_token, envvar_double)
{
	assert_expand_token("$HELLO $?", "Hello 255", 255);
}

Test(expand_token, envvar_single_quotes)
{
    assert_expand_token("\'$VAR\'", "$VAR", 0);
}

Test(expand_token, echo_shell_shell_ja)
{
	assert_expand_token("$HELLO$HELLOja", "Hello", 0);
}

Test(expand_token, echo_shell_shell_ja_in_single_quotes)
{
	assert_expand_token("$HELLO$HELLO\'ja\'", "HelloHelloja", 0);
}

Test(expand_token, echo_shell_shell_ja_in_double_quotes)
{
	assert_expand_token("$HELLO$HELLO\"ja\"", "HelloHelloja", 0);
}

Test(expand_token, echo_abcdef)
{
	assert_expand_token("a$VAR\'ef\'", "ab c def", 0);
}

Test(expand_token, echo_abcdef_empty_input)
{
	assert_expand_token("a$EMPTY\'ef\'", "aef", 0);
}

Test(expand_token, echo_a_and_b)
{
	assert_expand_token("a$A$B\"h\"", "ab c de f gh", 0);
}

Test(expand_token, echo_shell_single_and_double_quotes)
{
	assert_expand_token("\'$HELLO\'\"$HELLO\"",  "$HELLOHello", 0);
}

Test(expand_token, echo_shell_shell_quotes)
{
	assert_expand_token("$HELLO$HELLO\'\'", "HelloHello", 0);
}

Test(expand_token, echo_empty_input)
{
	assert_expand_token("  $EMPTY", "  ", 0);
}

Test(expand_token, envvar_single_quotes_1)
{
    assert_expand_token("\'$VAR\"\'", "$VAR\"", 0);
}

Test(expand_token, envvar_single_quotes_2)
{
    assert_expand_token("\'$VAR$\'", "$VAR$", 0);
}

Test(expand_token, double_quote_no_envvar)
{
    assert_expand_token("\"HELLO\"", "HELLO", 0);
}


Test(expand_token, double_quote_envvar)
{
    assert_expand_token("\"$HELLO\"", "Hello", 0);
}

Test(expand_token, double_quote_two_envvar)
{
    assert_expand_token("\"$HELLO$WORLD\"", "HelloWorld", 0);
}

Test(expand_token, envvar_with_spaces)
{
    assert_expand_token("echo $SPACE", "echo Spa ce", 0);
}

Test(expand_token, various_1)
{
    assert_expand_token("\"$? \'$?\' $?\"", "0 \'0\' 0", 0);
}

Test(expand_token, various_2)
{
	assert_expand_token("$?\'$?\"\'\"$?\"", "0$?\"0", 0);
}

Test(expand_token, various_3)
{
    assert_expand_token("\"$?\'$?\'\"$?\"\"", "0\'0\'0", 0);
}

Test(expand_token, various_4)
{
    assert_expand_token("echo $SPACE", "echo Spa ce", 0);
}

Test(expand_token, dollar_invalid_key)
{
	assert_expand_token("echo $z", "echo ", 0);
}

/*******************************************************************************/
/*                           Last_github_test_cases                            */
/*******************************************************************************/

Test(expand_token, dollar_digit_one)
{
	assert_expand_token("$1", "", 0);
}

Test(expand_token, dollar_digit_nine)
{
	assert_expand_token("$9", "", 0);
}

Test(expand_token, dollar_at_sign)
{
	assert_expand_token("$@", "", 0);
}

Test(expand_token, dollar_star)
{
	assert_expand_token("$*", "", 0);
}

// OUTPUT UNKNOWN
Test(expand_token, dollar_fence)
{
	assert_expand_token("$#", "", 0);
}

Test(expand_token, dollar_dash)
{
	assert_expand_token("$-","", 0);
}

Test(expand_token, dollar_underscore)
{
	assert_expand_token("$_", "", 0);
}

Test(expand_token, dollar_ifs)
{
	assert_expand_token("$IFS", "IFS", 0);
}

Test(expand_token, dollar_0)
{
	assert_expand_token("$0", "Sheldon", 0);
}

Test(expand_token, key_key_equal_sign_string_key)
{
	assert_expand_token("$HELLO$HELLO=lol$HELLO", "HelloHello=lolHello", 0);
}

Test(expand_token, dollar_in_double_quotes)
{
	assert_expand_token("\"$\"", "$", 0);
}

Test(expand_token, input_dollar_in_double_quotes_plus_char)
{
	assert_expand_token("\"$\"a", "$a", 0);
}
