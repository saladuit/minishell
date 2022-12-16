#include <minishell.h>

void	print_expo(char **expo)
{
	int32_t	i;

	i = 0;
	while (expo[i])
	{
		printf("%s\n", expo[i]);
		i++;
	}
}

int32_t	varname_len(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	sort_export(char **expo)
{
	int32_t	i;
	int32_t	smallest;
	char	*tmp;

	i = 0;
	while (expo[i])
	{
		if (expo[i + 1])
		{
			smallest = varname_len(expo[i]);
			if (smallest > varname_len(expo[i + 1]))
				smallest = varname_len(expo[i + 1]);
			if (ft_strncmp(expo[i], expo[i + 1], smallest) > 0)
			{
				tmp = expo[i];
				expo[i] = expo[i + 1];
				expo[i + 1] = tmp;
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

int	ft_export(char **arguments, t_minishell *shell)
{
	(void)arguments;
	// (void)shell;
	print_expo(shell->expo);
	return (0);
}
