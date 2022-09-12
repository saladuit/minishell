#include <stdio.h>
#include <string.h>
// #include "../libft.h"
#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned	const	char	*p;

	p = s;
	if (s == 0)
		return (0);
	while (*p)
	{
		if (*p == c)
		{
			return (p);
		}
		p++;
	}
	return (p);
}

int main ()
{
const char str1[] = "http://www.tutorialspoint.com";
const char ch1 = '.';
const char str2[] = "http://www.tutorialspoint.com";
const char ch2 = '\0';
char *ret;
ret = ft_strchr(str1, ch1);
printf("String after |%c| is - |%s|\n", ch1, ret);
ret = ft_strchr(str2, ch2);
printf("String after |%c| is - |%s|\n", ch2, ret);
ret = strchr(str1, ch1);
printf("String after |%c| is - |%s|\n", ch1, ret);
ret = strchr(str2, ch2);
printf("String after |%c| is - |%s|\n", ch2, ret);
return(0);
}