/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:04:29 by safoh         #+#    #+#                 */
/*   Updated: 2022/11/29 14:01:04 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdint.h>
# include <ft_tree.h>
# include <command.h>
# include <redir.h>

int32_t		execute(char *command_path, char **args, char **envp);
int32_t		executor(t_minishell *shell);
bool		protected_dup2(int fd, t_type type);
bool		open_redir(char *path, t_type type);
char		*get_redir_file(t_command *command, t_type type);
int			is_dir(char *path);
char		**get_env_paths(char **envp);
char		*check_env_paths(char **envp, char *cmd);
char		*get_cmd_path(char **envp, char *cmd);

#endif
