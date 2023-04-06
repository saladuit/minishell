#include <minishell.h>

static int numeric(char *arg)
{
	size_t i;

	i = 0;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	while (arg[i] && arg[i] == '0')
		i++;
	if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_minishell *shell)
{
	if (args[1] != NULL)
	{
		if (!numeric(args[1]))
			shell->status = E_UNKNOWN;
		else
		{
			shell->status = ft_atoi(args[1]) % 256;
			if (0 > shell->status)
				shell->status += 256;
		}
	}
	shell->stop = true;
	return (shell->status);
}
