/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_test.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 17:34:35 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/17 17:16:43 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <criterion/criterion.h>
# include <criterion/redirect.h>
# include <criterion/new/assert.h>
# include <minishell.h>

void	redirect_all_std(void);
void	assert_empty_stdout();
void	assert_error_stdout();

void	minishell_test(const char *envp[], const size_t count, int32_t expected);
void	tokenizer_test(const char input[], const char **expect, const int32_t ret);

#endif
