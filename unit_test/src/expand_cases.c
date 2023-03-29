#include <unit_test.h>

t_exitstatus zero = 0;
t_exitstatus max = 255;

 void setup_env(void)
 {
     setenv("HELLO", "Hello", 1);
	 setenv("$", "$", 1);
     setenv("WORLD", "World", 1);
     unsetenv("UNSET");
     setenv("SPACE", "Spa ce", 1);
 }

/*******************************************************************************/
/*                           Combine_expanded_strings                          */
/*******************************************************************************/

char *combine_expanded_strings(t_list *stack);

void assert_combine_expanded_strings(char **input, char *expected)
{
    t_list list;
    t_list list2;
    char *output;

    list.content = *input;
    if (input[1])
        list.next = &list2;
    else
        list.next = NULL;
    list2.content = *(input + 1);
    list2.next = NULL;
    output = combine_expanded_strings(&list);
    cr_expect_str_eq(output, expected);
    free(output);
}

Test(combine_expanded_strings, basic)
{
    char *input[] = {"Hallo", NULL};
    assert_combine_expanded_strings(input, "Hallo");
}

Test(combine_expanded_strings, two)
{
    char *input[] = {"Hallo", "Wereld", NULL};
    assert_combine_expanded_strings(input, "HalloWereld");
}

/*******************************************************************************/
/*                           Copy_until_quote_or_dollar                        */
/*******************************************************************************/

t_list *copy_until_quote_or_dollar(char *arg, size_t *i);

void assert_copy_until_quote_or_dollar(char *input, char *expected)
{
    t_list *output;
    size_t i;

    i = 0;
    output = copy_until_quote_or_dollar(input, &i);
    cr_expect_str_eq(output->content, expected);
    free(output->content);
    free(output);
}

Test(copy_until_quote_or_dollar, basic)
{
    char input[] = "Hallo";
    assert_copy_until_quote_or_dollar(input, "Hallo");
}

Test(copy_until_quote_or_dollar, dollar)
{
    char input[] = "Hallo$";
    assert_copy_until_quote_or_dollar(input, "Hallo");
}

Test(copy_until_quote_or_dollar, double_quote)
{
    char input[] = "Hallo\"";
    assert_copy_until_quote_or_dollar(input, "Hallo");
}

Test(copy_until_quote_or_dollar, single_quote)
{
    char input[] = "Hallo\'";
    assert_copy_until_quote_or_dollar(input, "Hallo");
 }

/*******************************************************************************/
/*                           Expand_Dollar                                     */
/*******************************************************************************/

char *expand_dollar(char *arg, t_exitstatus *status);

void assert_expand_dollar(char *input, char *expected, t_exitstatus *status)
{
    char *result = expand_dollar(input, status);
    cr_expect_str_eq(result, expected);
    free(result);
}

TestSuite(expand_dollar, .init=setup_env);

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

 Test(expand_dollar, double_var)
 {
     assert_expand_dollar("$HELLO$HELLO", "Hello", NULL);
 }

 Test(expand_dollar, null)
 {
     assert_expand_dollar("$UNSET", "", NULL);
 }

/*******************************************************************************/
/*                           Expand_double_quote_node                          */
/*******************************************************************************/

t_list *expand_double_quote_node(char *arg, size_t *i, t_exitstatus *status);

void assert_double_quote_node(char *input, char *expected)
{
    t_list *node;
    size_t i;

    i = 0;
    node = expand_double_quote_node(input, &i, &zero);
    cr_expect_str_eq(node->content, expected);
    cr_assert(node->next == NULL);
    free(node->content);
    free(node);
}

Test(expand_double_quote_node, basic)
{
    char input[] = {"\"Hallo\""};
    assert_double_quote_node(input, "Hallo");
}

// Test(expand_double_quote_node, single_envvar)
// {
//     char input[] = {"\"$HELLO\""};
//     assert_double_quote_node(input, "Hello");
// }

/*******************************************************************************/
/*                           Expand_single_quote_node                          */
/*******************************************************************************/

t_list *expand_single_quote_node(char *arg, size_t *i);

void assert_expand_single_quote_node(char *input, char *expected)
{
    t_list *node;
    size_t i;

    i = 0;
    node = expand_single_quote_node(input, &i);
    cr_expect_str_eq(node->content, expected);
    cr_assert(node->next == NULL);
    free(node->content);
    free(node);
}

/*******************************************************************************/
/*                           Expand_dollar_node                                */
/*******************************************************************************/

t_list *expand_dollar_node(char *arg, size_t *i, t_exitstatus *status);

void assert_expand_dollar_node(char *input, char *expected)
{
    t_list *node;
    size_t i;

    i = 0;
    node = expand_dollar_node(input, &i, &zero);
    cr_expect_str_eq(node->content, expected);
    cr_assert(node->next == NULL);
    free(node->content);
    free(node);
}

TestSuite(expand_dollar_node, .init=setup_env);

// Test(expand_dollar_node, double_envvar, .timeout=1)
// {
//     char input[] = "\"HELLO\"";
//     assert_expand_dollar_node(input, "Hello");
// }
//
// Test(expand_dollar_node, single_envvar, .timeout=1)
// {
//     char input[] = "$HELLO\"";
//     assert_expand_dollar_node(input, "Hello");
// }

Test(expand_dollar_node, two_envvar, .timeout=1)
{
    char input[] = "$HELLO$WORLD\"";
    assert_expand_dollar_node(input, "Hello");
}

/*******************************************************************************/
/*                           Are_quotes_closed                                 */
/*******************************************************************************/

//bool are_quotes_closed(const char *str);
//
//void assert_are_quotes_closed(char *input, bool expected)
//{
//    bool result = are_quotes_closed(input);
//    cr_assert(result == expected);
//}
//
//Test(quotes_closed, empty_string)
//{
//    assert_are_quotes_closed("", true);
//}
//
//Test(quotes_closed, no_quotes)
//{
//    assert_are_quotes_closed("this has no quotes", true);
//}
//
//Test(quotes_are_closed, single_quotes)
//{
//    assert_are_quotes_closed("this \'has\' single \'quotes\'", true);
//}
//
//Test(quotes_are_closed, double_quotes)
//{
//    assert_are_quotes_closed("this \"has\" double \"quotes\"", true);
//}
//
//Test(quotes_are_closed, unmatched_single_quotes)
//{
//    assert_are_quotes_closed("this \'has unmatched single quotes", false);
//}
//
//Test(quotes_are_closed, unmatched_double_quotes)
//{
//    assert_are_quotes_closed("this \"has unmatched double quotes", false);
//}
//
//Test(quotes_are_closed, mixed_quotes)
//{
//    assert_are_quotes_closed("this \'has \"both\" types\' of quotes", true);
//}
//
//// Test(quotes_are_closed, escaped_quotes)
//// {
////     assert_are_quotes_closed("this has escaped \"double\" quotes and \'\'single\' quotes", true);
//// }
//
//Test(quotes_are_closed, multiple_lines)
//{
//    assert_are_quotes_closed("this has quotes\non multiple\nlines", true);
//}
//
//// Test(quotes_are_closed, double_qutoes_with_single)
//// {
////     assert_are_quotes_closed("\'$SHLVL\"\'", true);
//// }

/*******************************************************************************/
/*                           Expand_token                                      */
/*******************************************************************************/

char *expand_token(char *arg, t_exitstatus *status);

TestSuite(expand_token, .init=setup_env);

void assert_expand_token(char *in, char *expected, t_exitstatus *status)
{
    char *input;
    input = ft_strdup(in);
    char *output = expand_token(input, status);
    cr_expect_str_eq(output, expected);
    free(output);
    free(input);
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

// FAILS
Test(expand_token, envvar_double_dollar)
{
	assert_expand_token("$$", "$", NULL);
}

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

// Test(expand_token, envvar_single_quotes_1)
// {
//     assert_expand_token("\'$VAR\"\'", "$VAR\"", NULL);
// }

Test(expand_token, envvar_single_quotes_2)
{
    assert_expand_token("\'$VAR$\'", "$VAR$", NULL);
}

Test(expand_token, double_qoute_no_envvar, .timeout=1)
{
    assert_expand_token("\"HELLO\"", "HELLO", NULL);
}

Test(expand_token, double_qoute_envvar, .timeout=1)
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
