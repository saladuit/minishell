#include <minishell.h>

int	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;
	char	*dir;

	dir = arguments[1];
	if (!dir)
	{
		dir = dict_get(&shell->env, "HOME");
		if (!dir)
		{
			ft_putstr_fd("cd: no home directory found\n", STDERR_FILENO);
			shell->status = E_BUILTIN;
			return (1);
		}
	}
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: error changing directory\n", STDERR_FILENO);
		shell->status = E_BUILTIN;
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd || arguments[0][0] == 'a')
	{
		ft_putstr_fd("cd: error getting current directory\n", STDERR_FILENO);
		shell->status = E_BUILTIN;
		return (1);
	}
	if (dict_set(&shell->env, "PWD", cwd) == ERROR)
	{
		ft_putstr_fd("cd: error setting PWD environment variable\n",
						STDERR_FILENO);
		free(cwd);
		shell->status = E_BUILTIN;
		return (1);
	}
	free(cwd);
	return (0);
}
