#include "../libft.h"
#include "/usr/include/bsd/string.h"
#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
    size_t i;
    
    i = 0;
    while (s[i])
    {
       ft_putchar(s[i], fd);
       ft_putchar('\n', fd);
       i++;
    }
}

int main()
{
    ft_putendl_fd("Hallo", 1);
}