#include "../libft.h"
#include "/usr/include/bsd/string.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*dest;
	size_t		len;

	if ((s == 0) || (f == 0))
		return (0);
	len = strlen(s);
	dest = (char*)malloc((len + 1) * sizeof(char));
	if (dest == 0)
		return (0);
	dest[len] = '\0';
	len = 0;
	while (s[len] != 0)
	{
		dest[len] = (*f)(len, s[len]);
		len++;
	}
	return (dest);
}

char odd_toupper(unsigned int i, char c)
{
    if (i % 2 == 0)
        return (tolower(c));
    return (toupper(c));
}

int main()
{
    char *pt;
    char str[25] = "Hallo maarten de grote";

    pt = ft_strmapi(str, &odd_toupper);
    puts(pt);
}