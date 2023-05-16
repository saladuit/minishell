#include <unit_test.h>


TestSuite(lexer, .init=redirect_all_std);

/*******************************************************************************/
/*                           Lexer_one                                         */
/*******************************************************************************/

void assert_lexer_one(char *command_line, char **expected)
{
    t_list *tokens;
    int32_t condition;
    t_status status;

    status = 0;
    set_malloc_failure_condition(0);
    tokens = lexer(command_line, &status);
    condition = get_malloc_failure_condition();
    cr_assert(tokens != NULL, "Expected test function to return a list of tokens.");
    cr_expect_str_eq(tokens->content, *expected);
    cr_expect(tokens->next == NULL);
    ft_lstclear(&tokens, free);
    while (condition > 0)
    {
        activate_malloc_hook();
        set_malloc_failure_condition(condition);
        tokens = lexer(command_line, &status);
        deactivate_malloc_hook();
        cr_assert_null(tokens, "Expected test function to return NULL on malloc failure.");
        condition--;
    }
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

Test(lexer, single_quote_in_double_quotes_and_vice_versa_one_node)
{
    char *expected[] = {"\"'\"'\"'", NULL};
    assert_lexer_one("\"'\"'\"'", expected);
}

Test(lexer, double_quote_in_single_quotes)
{
    char *expected[] = {"'\"'", NULL};
    assert_lexer_one("'\"'", expected);
}

Test(lexer, single_quote_in_double_quotes)
{
    char *expected[] = {"\"'\"", NULL};
    assert_lexer_one("\"'\"", expected);
}

/*******************************************************************************/
/*                           Lexer_two                                         */
/*******************************************************************************/

void assert_lexer_two(char *command_line, char **expected)
{
    t_list *tokens;
    t_status status;
    int32_t condition;

    status = 0;
    set_malloc_failure_condition(0);
    tokens = lexer(command_line, &status);
    condition = get_malloc_failure_condition();
    cr_assert(tokens != NULL, "Expected test function to return a list of tokens.");
    cr_expect_str_eq(tokens->content, *expected++);
    cr_expect_str_eq(tokens->next->content, *expected);
    cr_expect(tokens->next->next == NULL);
    ft_lstclear(&tokens, free);
    while (condition > 0)
    {
        activate_malloc_hook();
        set_malloc_failure_condition(condition);
        tokens = lexer(command_line, &status);
        deactivate_malloc_hook();
        cr_assert_null(tokens, "Expected test function to return NULL on malloc failure.");
        condition--;
    }
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

Test(lexer, single_quote_in_double_quotes_and_vice_versa_two_nodes)
{
    char *expected[] = {"\"'\"", "'\"'", NULL};
    assert_lexer_two("\"'\" '\"'", expected);
}

/*******************************************************************************/
/*                           null_Lexer                                        */
/*******************************************************************************/


void assert_lexer_null(char *command_line, char *message)
{
    t_list *tokens;
    t_status status;

    status = 0;
    tokens = lexer(command_line, &status);
    cr_assert_null(tokens, "Expected lexer to return NULL on error.");
    fflush(stderr);
    cr_assert_stderr_eq_str(message);
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

Test(lexer, null_input_output)
{
	assert_lexer_null("<>", "sheldon: syntax error near unexpected token `newline'\n");
}

Test(lexer, null_pipe_double)
{
    assert_lexer_null("||", "sheldon: syntax error near unexpected token `||'\n");
}

Test(lexer, null_exit_pipe)
{
    assert_lexer_null("exit|", "sheldon: syntax error near unexpected token `|'\n");
}

Test(lexer, null_pipe_exit)
{
    assert_lexer_null("|exit", "sheldon: syntax error near unexpected token `|'\n");
}

Test(lexer, null_two_pipes_exit)
{
	assert_lexer_null("||exit", "sheldon: syntax error near unexpected token `||'\n");
}

Test(lexer, null_three_pipes_exit)
{
	assert_lexer_null("|||exit", "sheldon: syntax error near unexpected token `||'\n");
}

Test(lexer, null_exit_three_pipes_exit)
{
	assert_lexer_null("exit|||exit", "sheldon: syntax error near unexpected token `|'\n");
}

Test(lexer, null_pipe_hallo_pipe_hallo)
{
	assert_lexer_null("|hallo|hallo", "sheldon: syntax error near unexpected token `|'\n");
}

Test(lexer, null_pipe_exit_output)
{
    assert_lexer_null("exit|<", "sheldon: syntax error near unexpected token `newline'\n");
}

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

Test(lexer, null_input_input)
{
	assert_lexer_null("< <", "sheldon: syntax error near unexpected token `<'\n");
}

Test(lexer, null_output_ouput)
{
	assert_lexer_null("> >", "sheldon: syntax error near unexpected token `>'\n");
}

Test(lexer, null_append_append)
{
	assert_lexer_null(">> >>", "sheldon: syntax error near unexpected token `>>'\n");
}

Test(lexer, null_heredoc_heredoc)
{
	assert_lexer_null("<< <<", "sheldon: syntax error near unexpected token `<<'\n");
}

/*******************************************************************************/
/*                           null_Lexer                                        */
/*******************************************************************************/


void assert_lexer_not_null(char *command_line)
{
    t_list *tokens;
    t_status status;

    status = 0;
    tokens = lexer(command_line, &status);
    cr_assert_not_null(tokens, "Expected lexer to return a list of tokens.");
    ft_lstclear(&tokens, free);
}

Test(lexer, not_null_lexer_valid_combo_1)
{
    assert_lexer_not_null("echo < Minishell | < Minishell echo | < Minishell echo ");
}

Test(lexer, not_null_lexer_valid_combo_2)
{
    assert_lexer_not_null("command1 | command2 > output.txt");
}

Test(lexer, not_null_lexer_valid_combo_3)
{
    assert_lexer_not_null("command1 | command2 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_4)
{
    assert_lexer_not_null("command1 | command2 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_5)
{
    assert_lexer_not_null("command1 > output.txt | command2");
}

Test(lexer, not_null_lexer_valid_combo_6)
{
    assert_lexer_not_null("command1 >> output.txt | command2");
}

Test(lexer, not_null_lexer_valid_combo_7)
{
    assert_lexer_not_null("command1 < input.txt | command2");
}

Test(lexer, not_null_lexer_valid_combo_8)
{
    assert_lexer_not_null("command1 << HERE | command2");
}

Test(lexer, not_null_lexer_valid_combo_9)
{
    assert_lexer_not_null("command1 << HERE | command2 > output.txt");
}

Test(lexer, not_null_lexer_valid_combo_10)
{
    assert_lexer_not_null("command1 << HERE | command2 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_11)
{
    assert_lexer_not_null("command1 << HERE | command2 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_12)
{
    assert_lexer_not_null("command1 << HERE | command2 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_13)
{
    assert_lexer_not_null("command1 < input.txt | command2 > output.txt | command3 < input2.txt");
}

Test(lexer, not_null_lexer_valid_combo_14)
{
    assert_lexer_not_null("command1 < input1.txt | command2 >> output.txt | command3 < input2.txt");
}

Test(lexer, not_null_lexer_valid_combo_15)
{
    assert_lexer_not_null("command1 << HERE | command2 << HERE2 | command3 > output.txt");
}

Test(lexer, not_null_lexer_valid_combo_16)
{
    assert_lexer_not_null("command1 | command2 << HERE | command3 > output.txt");
}

Test(lexer, not_null_lexer_valid_combo_17)
{
    assert_lexer_not_null("command1 > output.txt | command2 << HERE | command3");
}

Test(lexer, not_null_lexer_valid_combo_18)
{
    assert_lexer_not_null("command1 >> output.txt | command2 | command3 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_19)
{
    assert_lexer_not_null("command1 < input.txt | command2 | command3 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_20)
{
    assert_lexer_not_null("command1 << HERE | command2 | command3 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_21)
{
    assert_lexer_not_null("command1 << HERE | command2 > output.txt | command3 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_22)
{
    assert_lexer_not_null("command1 | command2 << HERE | command3 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_23)
{
    assert_lexer_not_null("command1 > output.txt | command2 << HERE | command3 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_24)
{
    assert_lexer_not_null("command1 >> output.txt | command2 < input.txt | command3");
}

Test(lexer, not_null_lexer_valid_combo_25)
{
    assert_lexer_not_null("command1 < input.txt | command2 >> output.txt | command3 << HERE");
}

Test(lexer, not_null_lexer_valid_combo_26)
{
    assert_lexer_not_null("command1 << HERE | command2 < input.txt | command3 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_27)
{
    assert_lexer_not_null("command1 | command2 < input.txt | command3 << HERE");
}

Test(lexer, not_null_lexer_valid_combo_28)
{
    assert_lexer_not_null("command1 > output.txt | command2 | command3 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_29)
{
    assert_lexer_not_null("command1 >> output.txt | command2 << HERE | command3 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_30)
{
    assert_lexer_not_null("command1 < input.txt | command2 | command3 >> output.txt << HERE");
}

Test(lexer, not_null_lexer_valid_combo_31)
{
    assert_lexer_not_null("command1 << HERE | command2 >> output.txt | command3 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_32)
{
    assert_lexer_not_null("command1 | command2 >> output.txt | command3 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_33)
{
    assert_lexer_not_null("command1 > output.txt << HERE | command2 | command3");
}

Test(lexer, not_null_lexer_valid_combo_34)
{
    assert_lexer_not_null("command1 >> output.txt | command2 < input.txt | command3 << HERE");
}

Test(lexer, not_null_lexer_valid_combo_35)
{
    assert_lexer_not_null("command1 < input.txt << HERE | command2 >> output.txt | command3");
}

Test(lexer, not_null_lexer_valid_combo_36)
{
    assert_lexer_not_null("command1 << HERE | command2 < input.txt | command3 >> output.txt << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_37)
{
    assert_lexer_not_null("command1 | command2 < input.txt | command3 << HERE >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_38)
{
    assert_lexer_not_null("command1 > output.txt | command2 << HERE | command3 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_39)
{
    assert_lexer_not_null("command1 >> output.txt | command2 << HERE | command3 < input.txt << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_40)
{
    assert_lexer_not_null("command1 < input.txt | command2 | command3 >> output.txt << HERE");
}

Test(lexer, not_null_lexer_valid_combo_41)
{
    assert_lexer_not_null("command1 << HERE | command2 >> output.txt | command3 < input.txt");
}

Test(lexer, not_null_lexer_valid_combo_42)
{
    assert_lexer_not_null("command1 | command2 >> output.txt | command3 << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_43)
{
    assert_lexer_not_null("command1 > output.txt << HERE | command2 | command3");
}

Test(lexer, not_null_lexer_valid_combo_44)
{
    assert_lexer_not_null("command1 >> output.txt | command2 < input.txt | command3 << HERE");
}

Test(lexer, not_null_lexer_valid_combo_45)
{
    assert_lexer_not_null("command1 < input.txt << HERE | command2 >> output.txt | command3");
}

Test(lexer, not_null_lexer_valid_combo_46)
{
    assert_lexer_not_null("command1 << HERE | command2 < input.txt | command3 >> output.txt << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_47)
{
    assert_lexer_not_null("command1 | command2 < input.txt | command3 << HERE >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_48)
{
    assert_lexer_not_null("command1 > output.txt | command2 << HERE | command3 >> output.txt");
}

Test(lexer, not_null_lexer_valid_combo_49)
{
    assert_lexer_not_null("command1 >> output.txt | command2 << HERE | command3 < input.txt << HERE2");
}

Test(lexer, not_null_lexer_valid_combo_50)
{
    assert_lexer_not_null("command1 < input.txt | command2 > output.txt | command3 << HERE");
}
