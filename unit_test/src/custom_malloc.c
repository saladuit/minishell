#include <custom_malloc.h>

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
