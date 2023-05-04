/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   pair_cases.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:39:39 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:39:39 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

t_pair *create_pair(const char *key, const char *value)
{
    t_pair *pair = (t_pair *)malloc(sizeof(t_pair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

void test_pair_to_str(const char *key, const char *value, const char *expected)
{
    t_pair *pair = create_pair(key, value);
    char *result;;
    int32_t condition = 0;

    set_malloc_failure_condition(0);
    result = pair_to_str(pair);
    condition = get_malloc_failure_condition();
    cr_assert_str_eq(result, expected, "Expected '%s' but got '%s'", expected, result);
    free(result);
    while (condition)
    {
        set_malloc_failure_condition(condition);
        activate_malloc_hook();
        result = pair_to_str(pair);
        deactivate_malloc_hook();
        cr_assert_null(result, "Expected NULL but got '%s'", result);
        free(result);
        condition--;
    }
    pair_clean(pair);
}

Test(pair_to_str, systemic_tests)
{
    test_pair_to_str("key", "value", "key=value");
    test_pair_to_str("hello", "world", "hello=world");
    test_pair_to_str("empty", "", "empty=");
    test_pair_to_str("", "value", "=value");
}

Test(pair_to_str, boundary_tests)
{
    test_pair_to_str("a", "b", "a=b");
    test_pair_to_str("", "", "=");
}
