#include <stdio.h>
#include <string.h>
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char *ptr;

	ptr = (char*)s;
	while (n > 0)
	{
		(ptr)[n - 1] = ((char)c);
		n--;
	}
	return (s);
}

int main ()
{
char str[50];
strcpy(str,"This is string.h library function");
puts(str);
ft_memset(str,'$',7);
puts(str);
return(0);
}