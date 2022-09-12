#include <stdio.h>
#include "../libft.h"

static	int		ft_itoa_strlen(int n)
{
	int					len;

	len = (n <= 0) ? 1 : 0;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	long	int	buffer;
	size_t				len;
	char				*alnum;

	buffer = n;
	len = ft_itoa_strlen(n);
	alnum = ft_malloc(len + 1);
	if (!alnum)
		return (0);
	alnum[len--] = '\0';
	if (n == 0)
		alnum = '0';
	if (n < 0)
	{
		*alnum = '-';
		buffer *= -1;
	}
	while (buffer)
	{
		alnum[len--] = (buffer % 10) + '0';
		buffer /= 10;
	}
	return (alnum);
}

int main() {
   int number;
   printf("Enter a number: ");
   scanf("%d", &number);
   printf("You have entered: %s", ft_itoa(number));
}