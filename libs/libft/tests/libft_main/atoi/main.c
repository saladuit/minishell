#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../libft.h"

int main()
{
	int val;
	char str[20];
	int std;

	strcpy(str, "98993489");
	val = ft_atoi(str);
	std = atoi(str);
	printf("String value = %d, Int value = %d\n", std, val);

	strcpy(str, "tutorialspoint.com");
	val = ft_atoi(str);
	std = atoi(str);
	printf("String value = %d, Int value = %d\n", std, val);

	return (0);
}