/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:04:29 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/19 15:39:25 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdint.h>
# include <ft_tree.h>
# include <command.h>

int32_t	execute(char **args, char **envp);
int32_t	executor(t_list *abstract_syntax_tree);

#endif
