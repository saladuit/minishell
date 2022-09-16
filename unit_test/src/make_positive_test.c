/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   make_positive_test.c                            |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/04 11:39:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/16 15:40:03 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

void	make_positive_test(const int len, int *input, const int *expected)
{
	size_t	i;

	i = 0;
	make_positive(len, input);
	while (i < (size_t)len)
	{
		cr_assert(eq(int, input[i], expected[i]));
		i++;
	}
}
