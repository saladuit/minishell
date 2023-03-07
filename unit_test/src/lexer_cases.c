#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <unit_test.h>
#include "libft.h"

extern t_exitstatus zero;
extern t_exitstatus max;

/*******************************************************************************/
/*                           Lexer                                             */
/*******************************************************************************/

t_list	*lexer(const char *command_line, t_exitstatus *exit_status);

void assert_lexer(char *command_line, char **expected)
{
    t_list *tokens;
    t_list *head;

    tokens = lexer(command_line, &zero);
    head = tokens;
    while (tokens)
    {
      cr_assert_not_null(expected);
      cr_expect_str_eq(tokens->content, *expected++);
      tokens = tokens->next;
    }
    ft_lstclear(&head, free);
}

Test(lexer, basic)
{
    char *expected[] = {"ls", NULL};
    assert_lexer("ls", expected);
}
Test(lexer, pipe)
{
    char *expected[] = {"|", NULL};
    assert_lexer("|", expected);
}

Test(lexer, input)
{
    char *expected[] = {"<", NULL};
    assert_lexer("<", expected);
}

Test(lexer, ouput)
{
    char *expected[] = {">", NULL};
    assert_lexer(">", expected);
}

Test(lexer, append)
{
    char *expected[] = {">>", NULL};
    assert_lexer(">>", expected);
}

Test(lexer, heredoc)
{
    char *expected[] = {"<<", NULL};
    assert_lexer("<<", expected);
}

Test(lexer, pipe_double)
{
    char *expected[] = {"|", "|", NULL};
    assert_lexer("||", expected);
}

Test(lexer, append_ouput)
{
    char *expected[] = {">>", ">", NULL};
    assert_lexer(">>>", expected);
}

Test(lexer, heredoc_input)
{
    char *expected[] = {"<<", "<", NULL};
    assert_lexer("<<<", expected);
}

// Test(lexer, dollar_double)
// {
//     char *expected[] = {"$", "$", NULL};
//     assert_lexer("$$", expected);
// }
//
// Test(lexer, dollar_envvar)
// {
//     char *expected[] = {"$", "$SHLVL", NULL};
//     assert_lexer("$$SHLVL", expected);
// }

Test(lexer, pipeline)
{
    char *expected[] = {"|", "ls", "-e$", ">>", ">", "|",  "<<", "<", NULL};
    assert_lexer("|ls -e$>>>|<<<", expected);
}
