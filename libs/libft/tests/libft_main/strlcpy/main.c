#include "../libft.h"
#include "/usr/include/bsd/string.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t	i;
// take the full size of the buffer

	i = 0;
// Also note that strlcpy() and strlcat() only operate on true “C” strings.
// This means that for strlcpy() src must be NUL-terminated
    if (dst == 0 || src == 0)
        return (0);
// The strlcpy() function copies up to size - 1 characters from the 
// NUL-terminated string src to dst, NUL-terminating the result.
    if (size > 0)
    {
	    while (size > 0 && i < size - 1 && src[i] != 0)
	    {
		    dst[i] = src[i];
		    i++;
	    }
// guarantee to NUL-terminate the result (as long as size is larger than 0
        dst[i] = '\0';
    }
// The strlcpy() and strlcat() functions return the total length of the string 
// they tried to create.  For strlcpy() that means the length of src.   
    while (src[i] != 0)
	     i++;
	return (i);
}
// Note: that a byte for the NUL should be included in size.

int main()
{
    char dest1[50] = {0};
    char dest2[50] = {0};
    char dest3[50] = {0};
    char dest4[50] = {0};
    char dest5[50] = {0};
    char dest6[50] = {0};
    char dest7[50] = {0};
    char dest8[50] = {0};
    char src[20] = {"hallo maarten"};

    ft_strlcpy(dest1, src, 2);
    puts(dest1);
    ft_strlcpy(dest2, src, 0);
    puts(dest2);
    ft_strlcpy(dest3, src, -1);
    puts(dest3);
    ft_strlcpy(dest4, src, 4);
    puts(dest4);
    strlcpy(dest5, src, 2);
    puts(dest5);
    strlcpy(dest6, src, 0);
    puts(dest6);
    strlcpy(dest7, src, -1);
    puts(dest7);
    strlcpy(dest8, src, 4);
    puts(dest8);
}