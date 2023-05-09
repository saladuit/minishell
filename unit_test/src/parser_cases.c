/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   parser_cases.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:39:43 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:39:43 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

extern char **environ;

TestSuite(parser, .init=redirect_all_std);

void assert_parser_printer(char *command_line)
{
  t_minishell sheldon;
  int32_t condition;

  bzero(&sheldon, sizeof(t_minishell));
  envp_load(&sheldon.env, environ);
  sheldon.tokens = lexer(command_line, &sheldon.status);
  sheldon.ast = parser(sheldon.tokens, &sheldon.status, &sheldon.env);
  cr_assert(sheldon.ast != NULL, "Expected test function to return a list of tokens.");
  set_malloc_failure_condition(0);
  debug_ast(sheldon.ast);
  condition = get_malloc_failure_condition();
  while (condition > 0)
  {
    activate_malloc_hook();
    set_malloc_failure_condition(condition);
    debug_ast(sheldon.ast);
    deactivate_malloc_hook();
    condition--;
  }
  deconstruct_ast(&sheldon.ast);
}

void assert_parser(char *command_line)
{
	t_minishell sheldon;
	int32_t condition;

	bzero(&sheldon, sizeof(t_minishell));
	envp_load(&sheldon.env, environ);
  sheldon.tokens = lexer(command_line, &sheldon.status);
  set_malloc_failure_condition(0);
  sheldon.ast = parser(sheldon.tokens, &sheldon.status, &sheldon.env);
  condition = get_malloc_failure_condition();
  cr_assert(sheldon.ast != NULL, "Expected test function to return a list of tokens.");
  debug_ast(sheldon.ast);
  deconstruct_ast(&sheldon.ast);
  while (condition > 0)
  {
    activate_malloc_hook();
    set_malloc_failure_condition(condition);
    sheldon.ast = parser(sheldon.tokens, &sheldon.status, &sheldon.env);
    deactivate_malloc_hook();
    cr_assert_null(sheldon.ast, "Expected test function to return NULL on malloc failure.");
    cr_assert(sheldon.status == E_GENERAL, "Expected test function to return E_GENERAL on malloc failure.");
    sheldon.status = 0;
    deconstruct_ast(&sheldon.ast);
    condition--;
  }
  ft_lstclear(&sheldon.tokens, free);
  dict_destroy(&sheldon.env);
}

Test(parser, ls_pipe_grep_output_input)
{
    assert_parser("ls < hello|grep a > holla | ls << hello | grep a >> hollaa");
}

Test(parser, all_printable_input)
{
    assert_parser_printer("ls < hello < hoi| grep a > holla | ls << hello | grep a >> hollaa | ls");
}

Test(parser, pint_ls)
{
    assert_parser_printer("ls");
}
