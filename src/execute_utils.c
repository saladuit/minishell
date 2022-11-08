#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <redir.h>
#include <command.h>


int	is_dir(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY);
	if (fd == -1 && errno == EISDIR)
	{
		return (1);
	}
	close(fd);
	return (0);
}

static bool	openfile(int *fd, char *path, t_type type)
{
	if (type == INPUT)
		*fd = open(path, O_RDONLY);
	if (type == OUTPUT)
		*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	protected_dup2(int fd, t_type type)
{
	int	ret;

	if (type == INPUT)
		ret = dup2(fd, STDIN_FILENO);
	if (type == OUTPUT)
		ret = dup2(fd, STDOUT_FILENO);
	if (ret == -1)
		return (false);
	return (true);
}

bool	open_redir(int *fd, char *path, t_type type)
{
	if (!openfile(fd, path, type))
		return (false);
	if (!protected_dup2(*fd, type))
		return (false);
	return (true);
}

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	return (paths);
}

char	*check_env_paths(char **envp, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*suffix;
	char	**paths;

	i = 0;
	cmd_path = NULL;
	paths = get_env_paths(envp);
	suffix = ft_strjoin("/", cmd);
	if (paths && suffix)
	{
		while (paths[i])
		{
			cmd_path = ft_strjoin(paths[i], suffix);
			if (!access(cmd_path, X_OK))
				break ;
			free(cmd_path);
			cmd_path = NULL;
			i++;
		}
	}
	free(suffix);
	ft_matrixfree(&paths);
	return (cmd_path);
}

char	*get_cmd_path(char **envp, char *cmd)
{
	char	*cmd_path;

	if (!cmd)
		return (0);
	if (ft_strncmp("./", cmd, 2) && ft_strncmp("/", cmd, 1))
	{
		cmd_path = check_env_paths(envp, cmd);
		if (cmd_path)
		{
			if (is_dir(cmd_path))
				return (free(cmd_path), NULL);
			return (cmd_path);
		}
	}
	if (!access(cmd, X_OK))
	{
		if (is_dir(cmd))
			return (NULL);
		return (cmd);
	}
	return (NULL);
}
