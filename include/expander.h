/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:04:07 by safoh         #+#    #+#                 */
/*   Updated: 2022/11/26 16:45:31 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <ft_tree.h>
# include <stdint.h>
# include <minishell.h>

int32_t	check_expand(char *str);
int32_t	is_double_quoted(char *str);
int32_t	is_single_quoted(char *str);
char	*strjoin_free_free(char *expanded, char *tmp);
int32_t	expander(t_minishell *shell);

#endif
