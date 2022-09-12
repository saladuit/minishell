#include <stdio.h>
#include <string.h>
#include <stddef.h>
// #include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	len;
	char	*p1;
	char	*p2;

	len = 0;
	p1 = (char *)dest;
	p2 = (char *)src;
	while (n > 0)
	{
		p1[len] = p2[len];
		n--;
		len++;
	}
	return (dest);
}

int main ()
{
const char dest[] = "oldstring";
const char src[] = "newstring";
printf("Before memmove dest = %s, src = %s\n", dest, src);
ft_memmove(((void*)dest), src, 9);
printf("After memmove dest = %s, src = %s\n", dest, src);
return(0);
}