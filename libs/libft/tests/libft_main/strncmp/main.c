#include <stdio.h>
#include <string.h>
#include "../libft.h"
#include <stddef.h>

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*p1;
	char	*p2;

	i = 0;
	j = 0;
	p1 = (unsigned char*)s1;
	p2 = (unsigned char*)s2;
	if (p1 == 0 || p2 == 0)
		return (0);
	// The  strcmp()  function compares the two strings s1 and s2.
	// it compares only the  first  (at  most)  n bytes of s1 and s2.
	while (i < n && (p1[i] != 0 || p2[i] != 0))
	{
	// It returns an integer less  than,  equal to, or greater than zero 
	// if s1 is found, respectively, to be less than, to match,
	// or be greater than s2.
		if (p1[i] != p2[i])
		{
			if (p1[i] < p2[i])
				return (-1);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int main ()
{
char str1[15];
char str2[15];
int ret;
strcpy(str1, "ABCDEF");
strcpy(str2, "abzdef");
ret = ft_strncmp(str1, str2, 6);
if(ret < 0)
{
printf("str1 is less than str2\n");
}
else if(ret > 0)
{
printf("str2 is less than str1\n");
}
else
{
printf("str1 is equal to str2\n");
}
return(0);
}