#include <minitype.h>
#include <stdbool.h>

bool	is_quote(int c)
{
	return (is_double_quote(c) || is_single_quote(c));
}
