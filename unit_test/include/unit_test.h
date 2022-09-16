/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   unit_test.h                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/20 17:04:51 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/16 19:55:09 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <criterion/criterion.h>
# include <criterion/new/assert.h>
# include <criterion/redirect.h>
# include "push_swap.h"
# include "actions.h"
# include "sort.h"
# include "init.h"
# include "argv_checker.h"

void	redirect_all_std(void);

void	argv_checker_test(const int len, const char **argv, \
		const bool expected);
void	array_check_test(const int len, const int *integer, \
		const int expected);

void	make_positive_test(const int len, int *input, const int *expected);
void	init_integer_array_test(const int len, const char **argv, \
		const int *expected);
void	init_stack_test(const int len, const int *array);
void	sort_array_test(const int len, const int *input, const int *expected);

void	push_swap_test(const int len, const char **argv, const bool expected);

#endif
