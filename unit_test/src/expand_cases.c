#include <unit_test.h>

void assert_expand_dollar(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_dollar(input, status);
    cr_assert_str_eq(result, expected);
    free(result);
}

TestSuite(expand_dollar);

Test(expand_dollar, single_dollar)
{
    t_exitstatus status = 0;

    assert_expand_dollar("$", "$", &status);
}

Test(expand_dollar, exit_status)
{
    t_exitstatus status = 0;

    assert_expand_dollar("$?", "0", &status);
}

Test(expand_dollar, single_var)
{
    t_exitstatus status = 0;
    setenv("TEST_VAR", "Hello World", 1);
    assert_expand_dollar("$TEST_VAR", "Hello World", &status);
    unsetenv("TEST_VAR");
}

Test(expand_dollar, basic)
{
    t_exitstatus status = 0;
    setenv("TEST_VAR", "Hello World", 1);
    unsetenv("TEST_VAR");
    assert_expand_dollar("$TEST_VAR", "", &status);
}

TestSuite(expand_arg);

void assert_expand_arg(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_arg_quote(input, 0, status);
    cr_assert_str_eq(result, expected);
    free(result);
}

Test(expand_arg, exit_status)
{
    t_exitstatus status = 0;
//
    assert_expand_arg("$?", "0", &status);
}

Test(expand_arg, basic)
{
    t_exitstatus status = 0;

    setenv("VAR", "Hello", 1);
    assert_expand_arg("$TEST_VAR", "Hello", &status);
    unsetenv("VAR");
}

Test(expand_arg, no_envvar)
{
    t_exitstatus status = 0;

    setenv("VAR", "Hello World", 1);
    unsetenv("VAR");
    assert_expand_arg("$TEST_VAR", "", &status);
}

Test(expand_arg, envvar_single_quotes)
{
    t_exitstatus status = 0;

    assert_expand_arg("'$TEST_VAR'", "$TEST_VAR", &status);
}

Test(expand_arg, envvar_double_qutoes)
{
    t_exitstatus status = 0;

    setenv("VAR", "Hello World", 1);
    assert_expand_arg("\"$TEST_VAR\"", "Hello World", &status);
    unsetenv("VAR");
}

Test(expand_arg, envvar_with_spaces)
{
    t_exitstatus status = 0;

    setenv("VAR", "Hello World", 1);
    assert_expand_arg("echo $TEST_VAR", "echo Hello World", &status);
    unsetenv("VAR");
}

void assert_expand_tokens(char *input, char *expected_output)
{
	t_exitstatus exit_status;
  t_list *arg_list;
  char *result;

	exit_status = 0;
  arg_list = ft_lstnew(ft_strdup(input));
  expand_tokens(&arg_list, &exit_status);
  result = arg_list->content;
  cr_log_error("Input: %s", input);
  cr_assert_str_eq(result, expected_output);
  ft_lstclear(&arg_list, free);
}

TestSuite(expand_tokens);

Test(expand_tokens, empty_input)
{
  assert_expand_tokens("", "");
}

Test(expand_tokens, no_expansion)
{
    assert_expand_tokens("hello world", "hello world");
}

Test(expand_tokens, simple_expansion)
{
    setenv("VAR", "value", 1);
    assert_expand_tokens("echo $VAR", "echo value");
}

Test(expand_tokens, multiple_expansions)
{
    setenv("VAR1", "value1", 1);
    setenv("VAR2", "value2", 1);
    assert_expand_tokens("echo $VAR1 $VAR2", "echo value1 value2");
}

Test(expand_tokens, expansion_in_single_quotes)
{
    setenv("VAR", "value", 1);
    assert_expand_tokens("'echo $VAR'", "echo $VAR");
}

Test(expand_tokens, expansion_in_double_quotes)
{
    setenv("VAR", "value", 1);
    assert_expand_tokens("\"echo $VAR\"", "echo value");
}

Test(expand_tokens, expansion_with_special_characters) {
    setenv("VAR", "value", 1);
    assert_expand_tokens("echo \"$VAR's\"", "echo \"value's\"");
}

Test(expand_tokens, expansion_with_undefined_variable) {
    assert_expand_tokens("echo $UNDEFINED", "echo ");
}

Test(expand_tokens, expansion_with_exit_status) {
    assert_expand_tokens("echo $?", "echo 123");
}

Test(expand_tokens, expansion_with_underscore) {
    assert_expand_tokens("echo $_", "echo minishell");
}
