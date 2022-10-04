/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:26:23 by safoh         #+#    #+#                 */
/*   Updated: 2022/10/04 16:41:34 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>

# include <message.h>
# include <lexer.h>
# include <parser.h>
# include <expander.h>
# include <executor.h>
# include <ft_tree.h>

int32_t	init_handlers(void);
int32_t	minishell(char **envp);

#endif
