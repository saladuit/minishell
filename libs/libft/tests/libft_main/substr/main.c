#include "../libft.h"
#include <stdio.h>
#include <string.h>

static	void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

static	char	*ft_strnew(size_t size)
{
	char	*str;

	if (size == __SIZE_MAX__)
		return (NULL);
	str = (char *)ft_memalloc(size + 1);
	return (str);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	dest = ft_strnew(len);
	if (!dest)
		return (NULL);
	ft_memcpy((void *)dest, (void *)&(s[start]), len);
	return (dest);
}

int main()
{
    char *pt;
    char *src = "Wat ik wil";

    pt = ft_substr(src, -1, 10);
    puts(pt);
}