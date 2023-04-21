#include <unit_test.h>
#include "custom_malloc.h"

/*******************************************************************************/
/*                              dict_delete                                    */
/*******************************************************************************/

Test(dict_delete, empty_dictionary)
{
    t_dictionary dict;
    bzero(&dict, sizeof(t_dictionary));

    dict_delete(&dict, "a");
    cr_assert_eq(dict.size, 0, "Deleting from an empty dictionary should not affect the size");
}


Test(dict_delete, non_existent_key)
{
    t_dictionary dict;
    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, "a", "value_a");
    dict_delete(&dict, "b");
    cr_assert_eq(dict.size, 1, "Deleting a non-existent key should not affect the size");
}

Test(dict_delete, single_key_no_collision)
{
    t_dictionary dict;
    char *key;
    char *value;

    key = strdup("a");
    value = strdup("value_a");
    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, key, value);
    dict_delete(&dict, key);
    cr_assert_eq(dict.size, 0, "Deleting a single key should result in an empty dictionary");
}

Test(dict_delete, delete_key_with_collision)
{
    t_dictionary dict;
    char *first_key;
    char *first_value;
    char *second_key;
    char *second_value;

    first_key = strdup("a");
    first_value = strdup("value_a");
    second_key = strdup("A");
    second_value = strdup("value_A");

    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, first_key, first_value);
    dict_set(&dict, second_key, second_value);

    dict_delete(&dict, first_key);

    cr_assert_eq(dict.size, 1, "Deleting one key in a collision should decrease the size by 1");
    cr_assert_not_null(dict.table[hash(second_key)], "The other key in the collision should remain");
    cr_assert_str_eq(dict.table[hash(second_key)]->key, second_key, "The remaining key should have the correct key");
    cr_assert_str_eq(dict.table[hash(second_key)]->value, second_value, "The remaining key should have the correct value");
}

Test(dict_delete, delete_last_key_in_collision_chain)
{
    t_dictionary dict;
    char *first_key;
    char *first_value;
    char *second_key;
    char *second_value;
    char *third_key;
    char *third_value;

    first_key = strdup("a");
    first_value = strdup("value_a");
    second_key = strdup("A");
    second_value = strdup("value_A");
    third_key = strdup("b");
    third_value = strdup("value_b");

    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, first_key, first_value);
    dict_set(&dict, second_key, second_value);
    dict_set(&dict, third_key, third_value);

    dict_delete(&dict, third_key);
    cr_assert_eq(dict.size, 2, "Deleting the last key in a collision chain should decrease the size by 1");
    cr_assert_null(dict.table[hash("b")], "The deleted key should no longer be in the dictionary");
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
}

Test(dict_to_envp, single_key_value)
{
    t_dictionary dict;
    char *key;
    char *value;

    key = strdup("a");
    value = strdup("value_a");
    bzero(&dict, sizeof(t_dictionary));
    dict_set(&dict, key, value);

    char **envp = dict_to_envp(&dict);

    cr_assert_not_null(envp, "The envp array should not be NULL");
    cr_assert_not_null(envp[0], "The first element should not be NULL");
    cr_assert_str_eq(envp[0], "a=value_a", "The envp should contain the correct key-value pair");
    cr_assert_null(envp[1], "The envp array should be NULL-terminated");
}

Test(dict_to_envp, multiple_key_values)
{
    t_dictionary dict;
    char *first_key;
    char *first_value;
    char *second_key;
    char *second_value;
    char *third_key;
    char *third_value;
    int32_t condition;

    first_key = strdup("a");
    first_value = strdup("value_a");
    second_key = strdup("b");
    second_value = strdup("value_b");
    third_key = strdup("c");
    third_value = strdup("value_c");

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
}
