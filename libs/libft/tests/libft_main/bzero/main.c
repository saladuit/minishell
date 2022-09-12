#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main ()
{
char str[50];
strcpy(str,"This is string.h library function");
puts(str);
ft_bzero(str, 5);
puts(str);
return(0);
}