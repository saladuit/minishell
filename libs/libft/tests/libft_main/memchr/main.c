#include <stdio.h>
#include <string.h>
// #include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned	const	char	*p;
	unsigned	char			ch;

	p = s;
	ch = c;
	if (p == 0)
		return (NULL);
	while (n)
	{
		if (*p == ch)
			// printf("%d", p);
			return ((void *)p);
		p++;
		n--;
	}
	return (NULL);
}

int main ()
{
const char str[] = "http://www.tutorialspoint.com";
const char ch = '.';
char *ret;
ret = ft_memchr(str, ch, strlen(str));
// printf("String after |%c| is - |%s|\n", ch, ret);
return(0);
}