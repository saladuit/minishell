#include <custom_malloc.h>
/* Example Usage
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
*/
static int g_malloc_hook_active = 0;
static int g_malloc_fail_count = 0;

void *malloc(size_t size)
{
  if (g_malloc_hook_active)
  {
    g_malloc_fail_count--;
    if (g_malloc_fail_count <= 0)
    {
      return NULL;
    }
  }
  else
    g_malloc_fail_count++;

  void *(*real_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
  return real_malloc(size);
}

void set_malloc_failure_condition(int condition)
{
    g_malloc_fail_count = condition;
}

void activate_malloc_hook(void)
{
    g_malloc_hook_active = 1;
}

void deactivate_malloc_hook(void)
{
    g_malloc_hook_active = 0;
}

int get_malloc_failure_condition(void)
{
    return g_malloc_fail_count;
}
