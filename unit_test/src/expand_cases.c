#include <unit_test.h>

t_exitstatus zero = 0;
t_exitstatus max = 255;

/*******************************************************************************/
/*                           Expand_Dollar                                     */
/*******************************************************************************/

void assert_expand_dollar(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_dollar(input, status);
    cr_expect_str_eq(result, expected);
    free(result);
}
void setup_expand_dollar(void)
{
     setenv("HELLO", "Hello", 1);
     unsetenv("NULL");
}

TestSuite(expand_dollar, .init=setup_expand_dollar);

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
     assert_expand_dollar("$?", "255", &max);
 }

 Test(expand_dollar, single_var)
 {
     assert_expand_dollar("$HELLO", "Hello", NULL);
 }

 Test(expand_dollar, null)
 {
     unsetenv("NULL");
     assert_expand_dollar("$NULL", "", NULL);
 }

/*******************************************************************************/
/*                           Expand_Arg                                        */
/*******************************************************************************/
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
     char *result = expand_token(input, status);
     cr_expect_str_eq(result, expected);
     free(result);
 }

 Test(expand_arg, basic_arg)
 {
     assert_expand_arg("Hello", "Hello", NULL);
 }

//Test(expand_arg, basic_env)
//{
//    assert_expand_arg("$HELLO", "Hello", NULL);
//}

// Test(expand_arg, exit_status)
// {
//     assert_expand_arg("$?", "0", &zero);
// }

// Test(expand_arg, exit_status_max)
// {
//     assert_expand_arg("$?", "0", &max);
// }
//
//
// Test(expand_arg, no_envvar)
// {
//     assert_expand_arg("$UNSET", "", NULL);
// }
//
// Test(expand_arg, envvar_single_quotes)
// {
//     assert_expand_arg("'$VAR'", "$VAR", NULL);
// }
//
// Test(expand_arg, envvar_double_qutoes)
// {
//     assert_expand_arg("\"$DQUOTE\"", "Hello World", NULL);
// }
//
// Test(expand_arg, envvar_with_spaces)
// {
//     assert_expand_arg("echo $SPACE", "echo Spa ce", NULL);
// }


/*******************************************************************************/
/*                           Are_quotes_closed                                 */
/*******************************************************************************/

// Define the test function using assert_quotes_closed
void test_are_quotes_closed(char *input, bool expected) {
    bool result = are_quotes_closed(input);
    cr_assert(result == expected);
}

Test(quotes_closed, empty_string) {
    test_are_quotes_closed("", true);
}

Test(quotes_closed, no_quotes) {
    test_are_quotes_closed("this has no quotes", true);
}

Test(quotes_are_closed, single_quotes) {
    test_are_quotes_closed("this 'has' single 'quotes'", true);
}

Test(quotes_are_closed, double_quotes) {
    test_are_quotes_closed("this \"has\" double \"quotes\"", true);
}

Test(quotes_are_closed, unmatched_single_quotes) {
    test_are_quotes_closed("this 'has unmatched single quotes", false);
}

Test(quotes_are_closed, unmatched_double_quotes) {
    test_are_quotes_closed("this \"has unmatched double quotes", false);
}

Test(quotes_are_closed, mixed_quotes) {
    test_are_quotes_closed("this 'has \"both\" types' of quotes", true);
}

Test(quotes_are_closed, escaped_quotes) {
    test_are_quotes_closed("this has escaped \\\"double\\\" quotes and \\'single\\' quotes", true);
}

Test(quotes_are_closed, multiple_lines) {
    test_are_quotes_closed("this has quotes\non multiple\nlines", true);
}

/*******************************************************************************/

// void assert_expand_tokens(char *input, char *expected_output)
// {
//   t_list *arg_list;
//   char *result;
//
//   arg_list = ft_lstnew(ft_strdup(input));
//   expand_tokens(&arg_list, &zero);
//   result = arg_list->content;
//   cr_log_error("Input: %s", input);
//   cr_expect_str_eq(result, expected_output);
//   ft_lstclear(&arg_list, cr_free);
// }
// void setup_expand_tokens(void)
// {
//     setenv("VAR", "value", 1);
//     setenv("ONE", "ONE", 1);
//     setenv("TWO", "TWO", 1);
//     setenv("QSINGLE", "noshow", 1);
//     setenv("QDOUBLE", "qduoble", 1);
//     unsetenv("UNDEFINED");
//     setenv("SPECIEAL_CHAR", "special_char", 1);
// }
//
// TestSuite(expand_tokens, .init=setup_expand_tokens);
//
// Test(expand_tokens, empty_input)
// {
//   assert_expand_tokens("", "");
// }
//
// Test(expand_tokens, no_expansion)
// {
//     assert_expand_tokens("hello world", "hello world");
// }
//
// Test(expand_tokens, simple_expansion)
// {
//     assert_expand_tokens("echo $VAR", "echo value");
// }
//
// Test(expand_tokens, multiple_expansions)
// {
//     assert_expand_tokens("echo $ONE $TWO", "echo one two");
// }
//
// Test(expand_tokens, expansion_in_single_quotes)
// {
//     assert_expand_tokens("'echo $QSINGLE'", "echo $QSINGLE");
// }
//
// Test(expand_tokens, expansion_in_double_quotes)
// {
//     assert_expand_tokens("\"echo $QDOUBLE\"", "echo qdouble");
// }
//
// Test(expand_tokens, expansion_with_special_characters) 
// {
//     assert_expand_tokens("echo \"$SPECIEAL_CHAR\"", "echo \"special_char\"");
// }
//
// Test(expand_tokens, expansion_with_undefined_variable) 
// {
//     assert_expand_tokens("echo $UNDEFINED", "echo ");
// }
//
// Test(expand_tokens, expansion_with_exit_status) {
//     assert_expand_tokens("echo $?", "echo 123");
// }
//
// Test(expand_tokens, expansion_with_underscore) 
// {
//     assert_expand_tokens("echo $_", "echo minishell");
// }
