#include <stdio.h>
#include<string.h>
#include "../libft.h"

int main() {
   char *str = "Helloworld";
   char *result;
   result = ft_strdup(str);
   printf("The string : %s", result);
   printf("%i", str == result);
   return 0;
}