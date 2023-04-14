#include <limits.h>

int	ft_ltoi_with_overflow(const char *str, long long *result)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	*result = 0;
	if (!str)
		return (1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		*result = *result * 10 + str[i] - '0';
		if (*result < 0 && *result != INT_MIN)
			return (0);
		i++;
	}
	*result *= sign;
	return (1);
}
