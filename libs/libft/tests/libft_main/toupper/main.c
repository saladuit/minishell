#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

int main()
{
int i = 0;
char c;
char str[] = "Tutorials Point";
while(str[i])
{
putchar (ft_toupper(str[i]));
i++;
}
return(0);
}