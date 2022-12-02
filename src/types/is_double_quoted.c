#include <libft.h>
#include <minitype.h>

bool	is_double_quoted(char *str)
{
	return (is_double_quote(str[0] && is_double_quote(str[ft_strlen(str) - 1])));
}
