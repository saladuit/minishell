/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   execute_child_command.c                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 17:51:29 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 17:51:29 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	file_exits(char *path)
{
	return (access(path, F_OK) == SUCCESS);
}

static char	*search_cmd_in_path(const char *path, const char *cmd)
{
	char	**path_dirs;
	char	*cmd_path;
	size_t	i;

	path_dirs = ft_split(path, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		cmd_path = ft_strjoin(path_dirs[i], cmd);
		if (!cmd_path)
			break ;
		if (file_exits(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	ft_matrixfree(&path_dirs);
	return (cmd_path);
}

static char	*get_cmd_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*slash_cmd;

	if (!path || !cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (file_exits(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	cmd_path = search_cmd_in_path(path, slash_cmd);
	free(slash_cmd);
	return (cmd_path);
}

void	execute_child_command(t_minishell *shell, char **arguments)
{
	char	*command_path;
	char	*path;
	char	**envp;

	path = dict_get(&shell->env, "PATH");
	command_path = get_cmd_path(path, arguments[0]);
	if (!command_path)
	{
		message_general_error(E_COMMAND_NOT_FOUND, NULL);
		_exit(E_COMMAND_NOT_FOUND);
	}
	envp = dict_to_envp(&shell->env);
	initialize_signal_handling_for_execve(&shell->status);
	execve(command_path, arguments, envp);
	message_system_call_error("execve");
	_exit(E_COMMAND_NOT_FOUND);
}
