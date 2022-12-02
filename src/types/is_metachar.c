#include <stdbool.h>

bool	ft_ismetachar(int c)
{
	return (c == '>' || c == '<' || c == '|');
}
