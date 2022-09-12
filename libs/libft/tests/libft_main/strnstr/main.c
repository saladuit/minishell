#include "../libft.h"
#include <stdio.h>
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	char *l;
	char *b;

	i = 0;
	j = 0;
	l = (char*)little;
	b = (char*)big;
	// error check
	if (little == 0 || big == 0)
		return (0);
	// If little is an empty string, big is returned
	if (*little == 0)
		return (b);
	// The strnstr() function locates the first occurrence 
	// of the null-terminated string little in the string big,
	// where not more than len characters are searched.
	// Characters that appear after a ‘\0’ character are not searched.
	while (i < len && b[i] != 0)
	{
		if (b[i] == l[j])
		{
			while (j + i < len && l[i])
			{
				if (b[i + j] != l[j])
					break;
					j++;
			}
	// a pointer to the first character of the first occurrence of
	// little is returned.
			if (l[j] == 0)
				return (b + i);
		}
		i++;
	}
	// if little occurs nowhere in big, NULL is returned
	return (NULL);
}

int main()
{
	char dest[50] = {"hallo maarten van codam"};
	char src[20] = {"maarten"};
	char *pt;

	pt = ft_strnstr(dest, src, 17);
	puts(pt);
	printf("%s/n", pt);
	// pt = strnstr(dest, src, 17);
	// puts(pt);
	// printf("%p/n", pt);
}