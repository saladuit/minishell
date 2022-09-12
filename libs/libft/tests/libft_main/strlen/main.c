#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../libft.h"

int main ()
{
char str[50];
int len;
strcpy(str, "This");
len = ft_strlen(str);
printf("Length of |%s| is |%d|\n", str, len);
return(0);
}