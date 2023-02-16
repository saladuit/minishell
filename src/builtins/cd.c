#include <minishell.h>
#include <unistd.h>
#include "libft.h"

//void	change_pwd(char *var, char *cwd, t_minishell *shell)
//{
//	char	*str;
//
//	str = ft_strjoin(var, cwd);
//	free(cwd);
//	if (in_env(str, shell->env))
//		export_replacevar(shell->env, str);
//	else
//		shell->env = export_addvar(shell->env, str);
//	if (in_env(str, shell->expo))
//		export_replacevar(shell->expo, str);
//	else
//		shell->expo = export_addvar(shell->expo, str);
//	free(str);
//}

int	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;
    char *dir = arguments[1];

    if (dir == NULL) 
	{
        dir = dict_get(&shell->envd, "HOME");
        if (dir == NULL) 
		{
            ft_putstr_fd("cd: no home directory found\n", STDERR_FILENO);
            return (E_BUILTIN);
        }
    }
    if (chdir(dir) == -1) 
	{
        ft_putstr_fd("cd: %s: %s\n", STDERR_FILENO);
        return (E_BUILTIN);
    }
    cwd = getcwd(NULL, 0);
    if (cwd == NULL) 
	{
        ft_putstr_fd("cd: error getting current directory\n", STDERR_FILENO);
        return (E_BUILTIN);
    }
    if (dict_set(&shell->envd, "PWD", cwd) == -1) 
	{
        ft_putstr_fd("cd: error setting PWD environment variable\n", STDERR_FILENO);
        free(cwd);
        return (E_BUILTIN);
    }
    free(cwd);
	return (0);
}
