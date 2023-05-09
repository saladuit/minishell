/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dict_cases.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:39:13 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:39:13 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                              dict_delete                                    */
/*******************************************************************************/

Test(dict_delete, empty_dictionary)
{
    t_dictionary dict;
    bzero(&dict, sizeof(t_dictionary));

    dict_remove_pair(&dict, "a");
    cr_assert_eq(dict.size, 0, "Deleting from an empty dictionary should not affect the size");
}


Test(dict_remove_pair, non_existent_key)
{
    t_dictionary dict;
    char *non_existent_key = "b";
	char *key = "a";
	char *value = "value_a";

    bzero(&dict, sizeof(t_dictionary));
	dict_set(&dict, key, value);
    dict_remove_pair(&dict, non_existent_key);
	cr_assert_eq(dict.size, 1, "Deleting a non-existent key should not affect the size");
	dict_destroy(&dict);
}

Test(dict_remove_pair, single_key_no_collision)
{
    t_dictionary dict;
    char *key;
    char *value;

    key = "a";
    value = "value_a";
    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, key, value);
    dict_remove_pair(&dict, key);
    cr_assert_eq(dict.size, 0, "Deleting a single key should result in an empty dictionary");
    dict_destroy(&dict);
}

Test(dict_remove_pair, delete_key_with_collision)
{
    t_dictionary dict;
    char *first_key;
    char *first_value;
    char *second_key;
    char *second_value;

    first_key = "a";
    first_value = "value_a";
    second_key = "A";
    second_value = "value_A";

    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, first_key, first_value);
    dict_set(&dict, second_key, second_value);

    dict_remove_pair(&dict, first_key);

    cr_assert_eq(dict.size, 1, "Deleting one key in a collision should decrease the size by 1");
    cr_assert_not_null(dict.table[hash(second_key)], "The other key in the collision should remain");
    cr_assert_str_eq(dict.table[hash(second_key)]->key, second_key, "The remaining key should have the correct key");
    cr_assert_str_eq(dict.table[hash(second_key)]->value, second_value, "The remaining key should have the correct value");

    // free(first_key);
    // free(first_value);
    // free(second_key);
    // free(second_value);
    dict_destroy(&dict);
}

Test(dict_delete, delete_last_key_in_collision_chain)
{
    t_dictionary dict;
    char	*first_key = "a";
	char	*first_value = "value_a";
	char	*second_key = "A";
	char	*second_value = "value_A";
	char	*third_key = "b";
	char	*third_value = "value_b";

    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, first_key, first_value);
    dict_set(&dict, second_key, second_value);
    dict_set(&dict, third_key, third_value);

    dict_remove_pair(&dict, third_key);
    cr_assert_eq(dict.size, 2, "Deleting the last key in a collision chain should decrease the size by 1");
    cr_assert_null(dict.table[hash("b")], "The deleted key should no longer be in the dictionary");
    dict_destroy(&dict);
}

/*******************************************************************************/
/*                              dict_to_envp                                   */
/*******************************************************************************/


Test(dict_to_envp, empty_dictionary)
{
    t_dictionary dict;

    bzero(&dict, sizeof(t_dictionary));

    char **envp = dict_to_envp(&dict);
    cr_assert_not_null(envp, "The envp array should not be NULL for an empty dictionary");
    cr_assert_null(envp[0], "The envp array should be NULL-terminated");
    ft_matrixfree(&envp);
}

Test(dict_to_envp, single_key_value)
{
    t_dictionary dict;
    char *key = "a";
    char *value = "value_a";

    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, key, value);

    char **envp = dict_to_envp(&dict);

    cr_assert_not_null(envp, "The envp array should not be NULL");
    cr_assert_not_null(envp[0], "The first element should not be NULL");
    cr_assert_str_eq(envp[0], "a=value_a", "The envp should contain the correct key-value pair");
    cr_assert_null(envp[1], "The envp array should be NULL-terminated");
    ft_matrixfree(&envp);
    dict_destroy(&dict);
}

Test(dict_to_envp, multiple_key_values)
{
    t_dictionary dict;
	char		*first_key = "a";
	char		*first_value = "value_a";
	char		*second_key = "b";
	char		*second_value = "value_b";
	char		*third_key = "c";
	char		*third_value = "value_c";
    int32_t		condition;

    bzero(&dict, sizeof(t_dictionary));

    dict_set(&dict, first_key, first_value);
    dict_set(&dict, second_key, second_value);
    dict_set(&dict, third_key, third_value);

    set_malloc_failure_condition(0);
    char **envp = dict_to_envp(&dict);
    condition = get_malloc_failure_condition();

    cr_assert_not_null(envp, "The envp array should not be NULL");
    cr_assert_str_eq(envp[0], "a=value_a");
    cr_assert_str_eq(envp[1], "b=value_b");
    cr_assert_str_eq(envp[2], "c=value_c");
    cr_assert_null(envp[3], "The envp array should be NULL-terminated");

    ft_matrixfree(&envp);

    while (condition > 0)
    {
        activate_malloc_hook();
        set_malloc_failure_condition(condition);
        envp = dict_to_envp(&dict);
        deactivate_malloc_hook();
        cr_assert_null(envp, "The envp array should be NULL. condition: %d", condition);
        ft_matrixfree(&envp);
        condition--;
    }
    dict_destroy(&dict);
}
