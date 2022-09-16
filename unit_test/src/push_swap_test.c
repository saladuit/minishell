/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   push_swap_test.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/27 14:53:58 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/16 15:29:16 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

void	push_swap_test(const int len, const char **argv, const bool expected)
{
	bool	submitted;
	char	*input;

	input = ft_joinmatrix(argv, len);
	submitted = push_swap(len, argv);
	cr_assert(submitted == expected,
		"Called:\tpush_swap_test()\nargv:\t\t%s\nlen:\t\t%d\n\
		expected:\t%s \nsubmitted:\t%s\n",
		input,
		len,
		expected,
		submitted);
	return ;
}
