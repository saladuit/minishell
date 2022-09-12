#include "../libft.h"
#include "/usr/include/bsd/string.h"
#include <stdio.h>
#include <ctype.h>

int main()
{
    char *pt;
    char str[] = "    1   Hallo maarten de grote    ";
    pt = ft_strtrim(str, NULL);
    puts(pt);
}