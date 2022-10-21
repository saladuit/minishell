#include <stdbool.h>

bool	ft_ismetachar(const char meta_c)
{
	if (meta_c == '>' || meta_c == '<' || meta_c == '|')
		return (true);
	return (false);
}
