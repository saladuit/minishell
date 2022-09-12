#include <stdio.h>
#include <string.h>
#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;
    char *p;
    char *curr;
	
	i = 0;
    p = (char*)s;
    curr = NULL;
	while (p[i] != '\0' + 1)
	{
		if (p[i] == c)
			curr = &p[i];     
		i++;
	}
	return (curr);   
}

int main ()
{
int len;
const char str1[] = "http://www.tutorialspoint.com";
const char ch1 = '.';
const char str2[] = "http://www.tutorialspoint.com";
const char ch2 = '\0';
char *ret;
ret = ft_strrchr(str1, ch1);
printf("String after |%c| is - |%s|\n", ch1, ret);
ret = ft_strrchr(str2, ch2);
printf("String after |%c| is - |%s|\n", ch2, ret);
ret = strrchr(str1, ch1);
printf("String after |%c| is - |%s|\n", ch1, ret);
ret = strrchr(str2, ch2);
printf("String after |%c| is - |%s|\n", ch2, ret);
return(0);
}