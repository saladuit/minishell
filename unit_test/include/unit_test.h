

/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   unit_test.h                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/03/25 17:34:35 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/20 11:09:28 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <criterion/criterion.h>
# include <criterion/new/assert.h>
# include <criterion/new/memory.h>
# include <criterion/new/stream.h>
# include <criterion/alloc.h>
# include <criterion/abort.h>
# include <criterion/event.h>
# include <criterion/options.h>
# include <criterion/output.h>
# include <criterion/parameterized.h>
# include <criterion/stats.h>
# include <criterion/types.h>
# include <minishell.h>

void	redirect_all_std(void);
void	assert_empty_stdout();
void	assert_error_stdout();

char *expand_dollar(char *arg, t_exitstatus *status);
char *expand_arg_quote(char *arg, int in_single_quote, t_exitstatus *status);
//void	minishell_test(const char *envp[], const size_t count, int32_t expected);
//
//void	tokenizer_test(const char input[], const char **expect, const int32_t ret);
//void	lexer_test(const char input[], const char **expect, const int32_t ret);
//
//void	get_command_test(const char input[], char *expect[]);
//
//void	execute_test(const char *path, char **args, char **envp, const int32_t ret);
//void	get_redir_test(const char input[], const char *expect[]);

#endif
