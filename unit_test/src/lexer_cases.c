#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <unit_test.h>
#include "libft.h"

extern t_exitstatus zero;
extern t_exitstatus max;

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

t_list	*lexer(const char *command_line, t_exitstatus *exit_status);

/*******************************************************************************/
/*                           Lexer_one                                         */
/*******************************************************************************/

void assert_lexer_one(char *command_line, char **expected)
{
    t_list *tokens;

    tokens = lexer(command_line, &zero);
    cr_expect_str_eq(tokens->content, *expected);
    cr_expect(tokens->next == NULL);
    ft_lstclear(&tokens, free);
}

Test(lexer_one, ls)
{
    char *expected[] = {"ls", NULL};
    assert_lexer_one("ls", expected);
}

/*******************************************************************************/
/*                           Lexer_two                                         */
/*******************************************************************************/

void assert_lexer_two(char *command_line, char **expected)
{
    t_list *tokens;

    tokens = lexer(command_line, &zero);
    cr_expect_str_eq(tokens->content, *expected++);
    cr_expect_str_eq(tokens->next->content, *expected);
    cr_expect(tokens->next->next == NULL);
    ft_lstclear(&tokens, free);
}

Test(lexer_two, ls_l)
{
    char *expected[] = {"ls", "-l", NULL};
    assert_lexer_two("ls -l", expected);
}

/*******************************************************************************/
/*                           null_Lexer                                        */
/*******************************************************************************/

TestSuite(lexer, .init=redirect_all_std);

void assert_lexer_null(char *command_line, char *message)
{
    t_list *tokens;


    (void)message;
    tokens = lexer(command_line, &zero);

    fflush(stderr);
    cr_expect(tokens==NULL);
    ft_lstclear(&tokens, free);
    cr_assert_stderr_eq_str(message);
}

Test(lexer, null_pipe)
{

    assert_lexer_null("|", "bash: syntax error near unexpected token `|'\n");
}

//Test(lexer, null_input)
//{
//    assert_lexer_null("<", "bash: syntax error near unexpected token `|'");
//}
//
//Test(lexer, null_ouput)
//{
//    assert_lexer_null(">", "bash: syntax error near unexpected token `|'");
//}

//Test(lexer, null_append)
//{
//    assert_lexer_null(">>", "bash: syntax error near unexpected token `|'");
//}
//
//Test(lexer, null_heredoc)
//{
//    assert_lexer_null("<<", "bash: syntax error near unexpected token `|'");
//}
//
//Test(lexer, null_pipe_double)
//{
//    assert_lexer_null("||", "minishell: syntax error near unexpected token `||'");
//}
//
//Test(lexer, null_append_ouput)
//{
//    assert_lexer_null(">>>", "bash: syntax error near unexpected token `|'");
//}
//
//Test(lexer, null_heredoc_input)
//{
//    assert_lexer_null("<<<", "bash: syntax error near unexpected token `|'");
//}
//
// Test(lexer, null_dollar_double)
// {
//     assert_lexer_null("$ $", "bash: syntax error near unexpected token `|'");
// }
//
// Test(lexer, null_dollar_envvar)
// {
//     assert_lexer_null("$ $SHLVL", "bash: syntax error near unexpected token `|'");
// }

//Test(lexer, null_command)
//{
//    assert_lexer_null("echo");
//}
