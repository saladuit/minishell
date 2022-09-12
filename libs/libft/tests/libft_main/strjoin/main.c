#include <stdio.h>
#include <string.h>
#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t j;
	char *dest;

	if (!s1 || !s2)
		return (NULL);
	j = ft_strlen(s1) + ft_strlen(s2);
	dest = (char*)calloc(j, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest)
	{
		strncpy(dest, s1, ft_strlen(s1) + 1);
		strncat(dest, s2, ft_strlen(s2) + 1);
	}
	return (dest);
}

int main () {
   char src[50], dest[50];
   char *pt;

   strcpy(src,  "This is source");
   strcpy(dest, "This is destination");

   pt = ft_strjoin(dest, src);

   printf("Final destination string : |%s|", pt);
   
   return(0);
}
