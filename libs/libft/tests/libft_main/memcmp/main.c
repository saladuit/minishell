#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
    int     len;
    char    *p1;
    char    *p2;
    
    len = 0;
    p1 = (char*)s1;
    p2 = (char*)s2;
    if (n == 0)
        return (0);
    while (n > 0)
    {
        if (p1[len] == p2[len])
        {
        n--;
        len++;
        }
        else
            return (p1[len] - p2[len]); 
    }    
}

int main ()
{
char str1[15];
char str2[15];
int ret;
memcpy(str2, "abcdef", 6);
memcpy(str1, "ABCDEF", 6);
ret = ft_memcmp(str1, str2, 6);
if(ret > 0)
{
printf("str2 is less than str1\n");
}
else if(ret < 0)
{
printf("str1 is less than str2\n");
}
else
{
printf("str1 is equal to str2\n");
}
return(0);
}