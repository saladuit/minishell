#include "../libft.h"
// #include "/usr/include/bsd/string.h"
#include <stdio.h>
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	
	d_len = ft_strlen(dst) - size;
	s_len = ft_strlen(src);
	if (dst == 0 || src == 0 || d_len == size)
		return (size + s_len);
	while (i < (size - d_len - 1) && src[i] != 0)
	{
		dst[i + d_len] = src[i];
		i++;
	}
	dst[i + d_len] = '\0';
	return (d_len + s_len);
}

int main()
{
	char dest1[50] = {"appelflap"};
	char dest2[50] = {"appelflap"};
	char dest3[50] = {"appelflap"};
	char dest4[50] = {"appelflap"};
	char dest5[50] = {"appelflap"};
	char dest6[50] = {"appelflap"};
	char dest7[50] = {"appelflap"};
	char dest8[50] = {"appelflap"};
	char src[20] = {"hallo maarten"};

	ft_strlcat(dest1, src, -1);
	puts(dest1);
	ft_strlcat(dest2, src, 0);
	puts(dest2);
	ft_strlcat(dest3, src, 1);
	puts(dest3);
	ft_strlcat(dest4, src, 20);
	puts(dest4);
	strlcat(dest5, src, -1);
	puts(dest5);
	strlcat(dest6, src, 0);
	puts(dest6);
	strlcat(dest7, src, 1);
	puts(dest7);
	strlcat(dest8, src, 20);
	puts(dest8);
}
