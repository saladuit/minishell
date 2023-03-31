#include <unit_test.h>

t_status zero = 0;
t_status max = 255;
extern char	**environ;

void setup_env(void)
{
    setenv("HELLO", "Hello", 1);
	setenv("$", "$", 1);
    setenv("WORLD", "World", 1);
    unsetenv("UNSET");
    setenv("SPACE", "Spa ce", 1);
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
    cr_expect_str_eq(output, expected);
    free(output);
    free(input);
	dict_destroy(env);
}


Test(expand_token, exit_status)
{
    assert_expand_token("$?", "0", &zero);
}

Test(expand_token, exit_status_max)
{
    assert_expand_token("$?", "255", &max);
}

Test(expand_token, empty)
{
    assert_expand_token("", "", NULL);
}

Test(expand_token, string)
{
    assert_expand_token("Hello", "Hello", NULL);
}

Test(expand_token, envvar_dollar)
{
    assert_expand_token("$", "$", NULL);
}

 // Test(expand_token, envvar_double_dollar)
 // {
 //     assert_expand_token("$$", "$$", NULL);
 // }


// Test(expand_token, envar_dollar_with_space_and_letter)
// {
//     assert_expand_token("$ a", "$ a", NULL);
// }

Test(expand_token, envvar_not_set)
{
    assert_expand_token("$UNSET", "", NULL);
}

Test(expand_token, envvar_single)
{
    assert_expand_token("$HELLO", "Hello", NULL);
}

// Test(expand_token, envvar_double)
// {
//     assert_expand_token("$HELLO $?", "Hello 255", &max);
// }

Test(expand_token, envvar_var_combo_1)
{
    assert_expand_token("$HELLO", "Hello", NULL);
}

Test(expand_token, envvar_var_combo_2)
{
    assert_expand_token("$HELLO", "Hello", NULL);
}

Test(expand_token, envvar_single_quotes)
{
    assert_expand_token("\'$VAR\'", "$VAR", NULL);
}

// Test(expand_token, echo_shell_shell)
// {
// 	assert_expand_token("$SHELL$SHELL", "/bin/zsh/bin/zsh", NULL);
// }

// NEXT 3 FAILING
// Test(expand_token, echo_shell_shell_ja)
// {
// 	assert_expand_token("$SHELL$SHELLja", "/bin/zsh/bin/zshja", NULL);
// }

// Test(expand_token, echo_shell_shell_double_dollar)
// {
// 	assert_expand_token("$SHELL$SHELL$$$$", "/bin/zsh/bin/zsh$$", NULL);
// }

// Test(expand_token, echo_shell_shell_quotes)
// {
// 	assert_expand_token("$SHELL$SHELL\'\'", "/bin/zsh/bin/zsh", NULL);
// }

Test(expand_token, echo_hallo_in_quotes)
{
	assert_expand_token("\"hallo\"", "hallo", NULL);
}

//Test(expand_token, echo_shell_shell_quatro_dollar)
//{
//	assert_expand_token("$SHELL$SHELL''", "/bin/zsh/bin/zsh37793779", NULL);
//}

// Test(expand_token, envvar_single_quotes_1)
// {
//     assert_expand_token("\'$VAR\"\'", "$VAR\"", NULL);
// }

Test(expand_token, envvar_single_quotes_2)
{
    assert_expand_token("\'$VAR$\'", "$VAR$", NULL);
}


Test(expand_token, double_qoute_no_envvar)
{
    assert_expand_token("\"HELLO\"", "HELLO", NULL);
}


Test(expand_token, double_qoute_envvar)
{
    assert_expand_token("\"$HELLO\"", "Hello", NULL);
}

// Test(expand_token, double_qoute_two_envvar, .timeout=1)
// {
//     assert_expand_token("\"$HELLO$WORLD\"", "HelloWorld", NULL);
// }

// Test(expand_token, envvar_with_spaces)
// {
//     assert_expand_token("echo $SPACE", "echo Spa ce", NULL);
// }

// Test(expand_token, various_1)
// {
//     assert_expand_token("\"$? \'$?\' $?\"", "3 \'3\' 0", &zero);
// }

// Test(expand_token, various_2)
// {
//     assert_expand_token("$?\'$S?\"\'\"$?\"", "3$SHLVL\"3", &zero);
// }

// Test(expand_token, various_3)
// {
//     assert_expand_token("\"$SHLVL\'$SHLVL\'\"$SHLVL\"\"", "3\'3\'3", &zero);
// }

// Test(expand_token, various_4)
// {
//     assert_expand_token("echo $SPACE", "echo Spa ce", NULL);
// }
