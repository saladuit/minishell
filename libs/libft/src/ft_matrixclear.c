#include <stdlib.h>
void	ft_matrixfree(char ***string)
{
	size_t	i;

	i = 0;
	if (!*string)
		return ;
	while ((*string)[i])
	{
		free((*string)[i]);
		i++;
	}
	free(*string);
	*string = NULL;
}
