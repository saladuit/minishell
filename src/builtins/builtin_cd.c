/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 18:24:12 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/04 18:24:19 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cd_error_msg(t_status *status, char *msg, bool e_gen, bool *ret)
{
	ft_putstr_fd("cd: error ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	if (e_gen)
		*status = E_GENERAL;
	else
		*status = E_BUILTIN;
	*ret = true;
}

static void	validate_dir(t_minishell *shell, char **dir, bool *ret)
{
	*dir = dict_get(&shell->env, "HOME");
	if (!*dir)
		cd_error_msg(&shell->status,
			"no home directory found", false, ret);
}

static void	initialize_cd(char **cwd, char **dir, bool *ret, char *arg)
{
	*cwd = NULL;
	*dir = arg;
	*ret = false;
}

void	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;
	char	*dir;
	bool	ret;

	initialize_cd(&cwd, &dir, &ret, arguments[1]);
	if (!dir)
		validate_dir(shell, &dir, &ret);
	if (ret == true)
		return ;
	if (chdir(dir) == -1 && !ret)
	{
		cd_error_msg(&shell->status, "changing directory", false, &ret);
		return ;
	}
	if (!ret)
		cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		shell->status = message_system_call_error("getcwd");
		return ;
	}
	if (dict_set(&shell->env, "PWD", cwd))
		cd_error_msg(&shell->status,
			"setting PWD environment variable", true, &ret);
	free(cwd);
}
