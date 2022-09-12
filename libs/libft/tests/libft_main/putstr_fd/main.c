#include "../libft.h"
#include "/usr/include/bsd/string.h"
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
    size_t i;
    
    i = 0;
    while (s[i])
    {
       ft_putchar(s[i], fd);
       i++;
    }
}

int main()
{
    ft_putstr_fd("Hallo\n", 1);
}