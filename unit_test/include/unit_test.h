/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   unit_test.h                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:35:54 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:35:54 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <criterion/criterion.h>
# include <criterion/redirect.h>
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
# include <libft.h>
# include <criterion/assert.h>
# include <criterion/internal/assert.h>
# include <custom_malloc.h>

void redirect_all_std(void);
void redirect_stderr(void);
void redirect_stdout(void);
void redirect_stdin(void);

#endif
