#include <unit_test.h>

t_exitstatus zero = 0;
t_exitstatus max = 255;

void assert_expand_dollar(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_dollar(input, status);
    cr_expect_str_eq(result, expected);
    cr_free(result);
}

TestSuite(expand_dollar);

Test(expand_dollar, single_dollar)
{
    assert_expand_dollar("$", "$", NULL);
}

Test(expand_dollar, exit_status)
{
    assert_expand_dollar("$?", "0", &zero);
}

Test(expand_dollar, exit_status_max)
{
    assert_expand_dollar("$?", "0", &max);
}

Test(expand_dollar, single_var)
{
    setenv("VAR", "Hello World", 1);
    assert_expand_dollar("$VAR", "Hello World", NULL);
}

Test(expand_dollar, basic)
{
    unsetenv("VAR");
    assert_expand_dollar("$VAR", "", NULL);
}

void setup_expand_arg(void)
{
    setenv("HELLO", "Hello", 1);
    setenv("DQUOTE", "Hello", 1);
    unsetenv("UNSET");
    setenv("SPACE", "Spa ce", 1);
}

TestSuite(expand_arg, .init=setup_expand_arg);

void assert_expand_arg(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_arg_quote(input, 0, status);
    cr_expect_str_eq(result, expected);
    cr_free(result);
}

Test(expand_arg, exit_status)
{
    assert_expand_arg("$?", "0", &zero);
}

Test(expand_arg, exit_status_max)
{
    assert_expand_arg("$?", "0", &max);
}

Test(expand_arg, basic)
{
    assert_expand_arg("$HELLO", "Hello", NULL);
}

Test(expand_arg, no_envvar)
{
    assert_expand_arg("$UNSET", "", NULL);
}

Test(expand_arg, envvar_single_quotes)
{
    assert_expand_arg("'$VAR'", "$VAR", NULL);
}

Test(expand_arg, envvar_double_qutoes)
{
    assert_expand_arg("\"$DQUOTE\"", "Hello World", NULL);
}

Test(expand_arg, envvar_with_spaces)
{
    assert_expand_arg("echo $SPACE", "echo Spa ce", NULL);
}

void assert_expand_tokens(char *input, char *expected_output)
{
  t_list *arg_list;
  char *result;

  arg_list = ft_lstnew(ft_strdup(input));
  expand_tokens(&arg_list, &zero);
  result = arg_list->content;
  cr_log_error("Input: %s", input);
  cr_expect_str_eq(result, expected_output);
  ft_lstclear(&arg_list, cr_free);
}
void setup_expand_tokens(void)
{
    setenv("VAR", "value", 1);
    setenv("ONE", "ONE", 1);
    setenv("TWO", "TWO", 1);
    setenv("QSINGLE", "noshow", 1);
    setenv("QDOUBLE", "qduoble", 1);
    unsetenv("UNDEFINED");
    setenv("SPECIEAL_CHAR", "special_char", 1);
}

TestSuite(expand_tokens, .init=setup_expand_tokens);

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
    assert_expand_tokens("echo $VAR", "echo value");
}

Test(expand_tokens, multiple_expansions)
{
    assert_expand_tokens("echo $ONE $TWO", "echo one two");
}

Test(expand_tokens, expansion_in_single_quotes)
{
    assert_expand_tokens("'echo $QSINGLE'", "echo $QSINGLE");
}

Test(expand_tokens, expansion_in_double_quotes)
{
    assert_expand_tokens("\"echo $QDOUBLE\"", "echo qdouble");
}

Test(expand_tokens, expansion_with_special_characters) 
{
    assert_expand_tokens("echo \"$SPECIEAL_CHAR\"", "echo \"special_char\"");
}

Test(expand_tokens, expansion_with_undefined_variable) 
{
    assert_expand_tokens("echo $UNDEFINED", "echo ");
}

Test(expand_tokens, expansion_with_exit_status) {
    assert_expand_tokens("echo $?", "echo 123");
}

Test(expand_tokens, expansion_with_underscore) 
{
    assert_expand_tokens("echo $_", "echo minishell");
}
