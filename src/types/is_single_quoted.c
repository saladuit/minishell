#include <libft.h>
#include <minitype.h>

bool	is_single_quoted(char *str)
{
	return (is_single_quote(str[0] && is_single_quote(str[ft_strlen(str) - 1])));
}
