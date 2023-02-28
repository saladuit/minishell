#include <unit_test.h>

/*******************************************************************************/
/*                           Envp_laod                                         */
/*******************************************************************************/

int32_t envp_load(t_dictionary *env, char **envp);

void assert_envp_load(char **input,char *key, char *expected)
{
  t_dictionary env[HASH_TABLE_SIZE];

  envp_load(env, input);
  cr_expect_str_eq(dict_get(env, key), expected);
  dict_destroy(env);
}

TestSuite(envp_load);

Test(envp_load, basic)
{
  char *input[] = {"HELLO=Hello", NULL};
  assert_envp_load(input , "HELLO", "Hello");
}

Test(envp_load, empty)
{
  char *input[] = {"HELLO=", NULL};
  assert_envp_load(input , "HELLO", "");
}

Test(envp_load, dollar)
{
  char *input[] = {"DOLLAR=$", NULL};
  assert_envp_load(input , "DOLLAR", "$");
}
