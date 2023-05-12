/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   env_load_cases.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:39:23 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:39:23 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                           Envp_load                                         */
/*******************************************************************************/

TestSuite(envp_load, .init=redirect_all_std);

void assert_envp_load(char **input,char *key, char *expected)
{
  int condition;
  t_dictionary env[HASH_TABLE_SIZE];

  bzero(env, sizeof(env));
  set_malloc_failure_condition(0);
  envp_load(env, input);
  cr_expect_str_eq(dict_get(env, key), expected);
  condition = get_malloc_failure_condition();
  dict_destroy(env);
  while (condition > 0)
  {
    activate_malloc_hook();
    set_malloc_failure_condition(condition);
    bzero(env, sizeof(env));
    envp_load(env, input);
    deactivate_malloc_hook();
    cr_expect_null(dict_get(env, key), "Expected test function to return NULL on malloc failure.");
    condition--;
  }
}

Test(envp_load, null)
{
  t_dictionary env[HASH_TABLE_SIZE];

  bzero(env, sizeof(env));
  envp_load(env, NULL);
  dict_destroy(env);
}

Test(envp_load, basic)
{
  char *input[] = {"HELLO=Hello", NULL};
  assert_envp_load(input , "HELLO", "Hello");
}

Test(envp_load, empty_equals)
{
  char *input[] = {"HELLO=", NULL};
  assert_envp_load(input , "HELLO", "");
}

Test(envp_load, empty)
{
  char *input[] = {"HELLO", NULL};
  assert_envp_load(input , "HELLO", "");
}

Test(envp_load, dollar)
{
  char *input[] = {"DOLLAR=$", NULL};
  assert_envp_load(input , "DOLLAR", "$");
}
