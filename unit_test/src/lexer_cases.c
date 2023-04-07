#include <unit_test.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(lexer, .init=redirect_all_std);

// Test utility function
void test_malloc_failure(const char *command)
{
    t_status exit;
    int condition;
    t_list *tokens;

    exit = 0;
    set_malloc_failure_condition(0);
    tokens = lexer(command, &exit);
    ft_lstclear(&tokens, free);
    condition = get_malloc_failure_condition();
    while (condition > 0)
    {
        activate_malloc_hook();
        set_malloc_failure_condition(condition);
        tokens = lexer(command, &exit);
        deactivate_malloc_hook();
        cr_assert_null(tokens, "Expected test function to return NULL on malloc failure.");
        condition--;
    }
}

Test(lexer, malloc)
{
    test_malloc_failure("command");
}

Test(lexer, malloc_2)
{
    test_malloc_failure("command arg1 arg2");
}

/*******************************************************************************/
/*                           Lexer_one                                         */
/*******************************************************************************/

void assert_lexer_one(char *command_line, char **expected)
{
    t_list *tokens;
    t_status status;

    status = 0;
    tokens = lexer(command_line, &status);
    cr_expect_str_eq(tokens->content, *expected);
    cr_expect(tokens->next == NULL);
    ft_lstclear(&tokens, free);
}

Test(lexer, one_ls)
{
    char *expected[] = {"ls", NULL};
    assert_lexer_one("ls", expected);
}

Test(lexer, one_dollar)
{
   char *expected[] = {"$", NULL};
   assert_lexer_one("$", expected);
}

Test(lexer, one_expansion)
{
   char *expected[] = {"$HELLO", NULL};
   assert_lexer_one("$HELLO", expected);
}

/*******************************************************************************/
/*                           Lexer_two                                         */
/*******************************************************************************/

void assert_lexer_two(char *command_line, char **expected)
{
    t_list *tokens;
    t_status status;

    status = 0;
    tokens = lexer(command_line, &status);
    cr_expect_str_eq(tokens->content, *expected++);
    cr_expect_str_eq(tokens->next->content, *expected);
    cr_expect(tokens->next->next == NULL);
    ft_lstclear(&tokens, free);
}

Test(lexer, two_ls_l)
{
    char *expected[] = {"ls", "-l", NULL};
    assert_lexer_two("ls -l", expected);
}

Test(lexer, echo_dollar)
{
    char *expected[] = {"echo", "$", NULL};
    assert_lexer_two("echo $", expected);
}

Test(lexer, echo_hello)
{
	char *expected[] = {"echo", "hello", NULL};
	assert_lexer_two("echo hello", expected);
}

Test(lexer, dollar_dollar)
{
	char *expected[] = {"$", "$", NULL};
	assert_lexer_two("$ $", expected);
}

Test(lexer, echo_hello_with_quotes_one)
{
	char *expected[] = {"echo", "'he\"llo'", NULL};
	assert_lexer_two("echo 'he\"llo'", expected);
}

Test(lexer, echo_hello_with_quotes_two)
{
	char *expected[] = {"echo", "'hello'", NULL};
	assert_lexer_two("echo 'hello'", expected);
}

Test(lexer, echo_hello_with_quotes_three)
{
	char *expected[] = {"echo", "\"hel\'lo\"", NULL};
	assert_lexer_two("echo \"hel\'lo\"", expected);
}

Test(lexer, file_heredoc)
{
    char *expected[] = {"<<", "heredoc", NULL};
    assert_lexer_two("<<heredoc", expected);
}

Test(lexer, file_input)
{
    char *expected[] = {"<", "input", NULL};
    assert_lexer_two("<input", expected);
}

Test(lexer, file_output)
{
    char *expected[] = {">", "ouput", NULL};
    assert_lexer_two(">ouput", expected);
}

Test(lexer, file_append)
{
    char *expected[] = {">>", "append", NULL};
    assert_lexer_two(" >>append", expected);
}

Test(lexer, file_heredoc_space)
{
    char *expected[] = {"<<", "heredoc", NULL};
    assert_lexer_two(" <<\theredoc ", expected);
}

Test(lexer, file_input_space)
{
    char *expected[] = {"<", "input", NULL};
    assert_lexer_two(" <\tinput ", expected);
}

Test(lexer, file_output_space)
{
    char *expected[] = {">", "ouput", NULL};
    assert_lexer_two(" >\touput ", expected);
}

Test(lexer, file_append_space)
{
    char *expected[] = {">>", "append", NULL};
    assert_lexer_two(" >>\tappend ", expected);
}
/*******************************************************************************/
/*                           null_Lexer                                        */
/*******************************************************************************/

// possible test case -- multiple commands: "ls -l ; pwd | grep foo"

void assert_lexer_null(char *command_line, char *message)
{
    t_list *tokens;
    t_status status;

    status = 0;
    tokens = lexer(command_line, &status);
    fflush(stderr);
    cr_expect(tokens==NULL, "Expected lexer to return NULL on error.");
    ft_lstclear(&tokens, free);
    cr_expect_stderr_eq_str(message);
}

Test(lexer, null_pipe)
{
    assert_lexer_null("|", "sheldon: syntax error near unexpected token `|'\n");
}

Test(lexer, null_input)
{
    assert_lexer_null("<", "sheldon: syntax error near unexpected token `newline'\n");
}

Test(lexer, null_ouput)
{
    assert_lexer_null(">", "sheldon: syntax error near unexpected token `newline'\n");
}

Test(lexer, null_append)
{
    assert_lexer_null(">>", "sheldon: syntax error near unexpected token `newline'\n");
}

Test(lexer, null_heredoc)
{
    assert_lexer_null("<<", "sheldon: syntax error near unexpected token `newline'\n");
}

Test(lexer, null_pipe_double)
{
    assert_lexer_null("||", "sheldon: syntax error near unexpected token `||'\n");
}

// Test(lexer, null_exit_pipe)
// {
//     assert_lexer_null("exit|", "sheldon: syntax error near unexpected token `||'\n");
// }
//
// Test(lexer, null_pipe_exit)
// {
//     assert_lexer_null("|exit", "sheldon: syntax error near unexpected token `||'\n");
// }
//
// Test(lexer, null_pipe_exit_output)
// {
//     assert_lexer_null("exit|<", "sheldon: syntax error near unexpected token `||'\n");
// }

Test(lexer, null_append_output)
{
    assert_lexer_null(">> >", "sheldon: syntax error near unexpected token `>'\n");
}

Test(lexer, null_heredoc_input)
{
    assert_lexer_null("<< <", "sheldon: syntax error near unexpected token `<'\n");
}

Test(lexer, null_heredoc_input_two)
{
	assert_lexer_null("<< >", "sheldon: syntax error near unexpected token `>'\n");
}

Test(lexer, null_append_output_two)
{
	assert_lexer_null(">> <", "sheldon: syntax error near unexpected token `<'\n");
}

Test(lexer, null_append_output_nospace)
{
	assert_lexer_null(">><", "sheldon: syntax error near unexpected token `<'\n");
}

Test(lexer, pre_space_null_append_output_nospace)
{
	assert_lexer_null(" >><", "sheldon: syntax error near unexpected token `<'\n");
}

Test(lexer, null_quote_count_is_odd_one)
{
	assert_lexer_null("echo \'hel\'\'lo\'\'", "sheldon: quote is unclosed\n");
}

Test(lexer, null_quote_count_is_odd_two)
{
	assert_lexer_null("echo \'hello", "sheldon: quote is unclosed\n");
}

Test(lexer, null_quote_count_is_odd_three)
{
	assert_lexer_null("echo \"hel\"lo\"", "sheldon: quote is unclosed\n");
}

Test(lexer, null_quote_count_is_odd_four)
{
	assert_lexer_null("echo hello\"", "sheldon: quote is unclosed\n");
}

Test(lexer, null_exclamation_mark)
{
	assert_lexer_null("!", "sheldon: syntax error near unexpected token `newline'\n");
}

//Test(lexer, null_command)
//{
//    assert_lexer_null("echo");
//}
