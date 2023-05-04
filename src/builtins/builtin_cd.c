#include <minishell.h>

static void	cd_error_msg(t_status *status, char *msg, bool e_gen)
{
	ft_putstr_fd("cd: error ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	if (e_gen)
		*status = E_GENERAL;
	else
		*status = E_BUILTIN;
}

void	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;
	char	*dir;

	dir = arguments[1];
	if (!dir)
	{
		dir = dict_get(&shell->env, "HOME");
		if (!dir)
		{
			cd_error_msg(&shell->status,
								 "no home directory found", false);
			return ;
		}
	}
	if (chdir(dir) == -1)
	{
		cd_error_msg(&shell->status, "changing directory", false);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		shell->status = message_system_call_error("getcwd");
		return ;
	}
	if (dict_set(&shell->env, "PWD", cwd))
	{
		free(cwd), cd_error_msg(&shell->status,
										"setting PWD environment variable", true);
		return ;
	}
	free(cwd);
}
