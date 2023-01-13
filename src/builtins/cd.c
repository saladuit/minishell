#include <minishell.h>

void	change_pwd(char *var, char *cwd, t_minishell *shell)
{
	char	*str;

	str = ft_strjoin(var, cwd);
	free(cwd);
	if (in_env(str, shell->env))
		export_replacevar(shell->env, str);
	else
		shell->env = export_addvar(shell->env, str);
	if (in_env(str, shell->expo))
		export_replacevar(shell->expo, str);
	else
		shell->expo = export_addvar(shell->expo, str);
	free(str);
}

int	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;

	if (ft_matrixlen((void **)arguments) > 1)
	{
		cwd = getcwd(NULL, 0);
		if (chdir(arguments[1]) == -1)
		{
			write(STDERR_FILENO, "cd: ", 4);
			write(STDERR_FILENO, arguments[1], ft_strlen(arguments[1]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return (1);
		}
		else
		{
			change_pwd("OLDPWD=", cwd, shell);
			cwd = getcwd(NULL, 0);
			change_pwd("PWD=", cwd, shell);
		}
	}
	return (0);
}
