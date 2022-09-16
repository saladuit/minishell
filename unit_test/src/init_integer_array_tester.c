/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   init_integer_array_tester.c                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:18:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/16 15:26:51 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

void	init_integer_array_test(const int len, const char **argv, \
		const int *expected)
{
	int		*submitted;
	char	*input;

	input = ft_joinmatrix(argv, len);
	submitted = init_integer_array(len, argv);
	if (expected == NULL)
		cr_assert(zero(ptr, submitted),
			"Called:\t\tinit_integer_array()\nargv:\t\t%s\nlen:\t\t%d\n",
			input, len);
	else
		cr_assert_arr_eq(submitted, expected, len,
			"Called:\tinit_integer_array()\nargv:\t\t%s\nlen:\t\t%d\n",
			input,
			len);
}
