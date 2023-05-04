#include <minishell.h>

void	ft_unset(char **arguments, t_minishell *shell)
{
	size_t	i;

	i = 1;
	while (arguments[i])
		dict_remove_pair(&shell->env, arguments[i++]);
	return ;
}
