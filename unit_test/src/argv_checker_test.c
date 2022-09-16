/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   argv_checker_test.c                             |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/20 17:04:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/16 15:22:43 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

void	argv_checker_test(const int len, const char **argv, \
		const bool expected)
{
	bool	submitted;
	char	*input;

	input = ft_joinmatrix(argv, len);
	submitted = argv_checker(len, argv);
	cr_assert(submitted == expected,
		"Called:\targv_checker()\ninput:\t\t%s\nlen:\t\t%d\n\
		expected:\t%s\nsubmitted:\t%s\n",
		input,
		len,
		expected,
		submitted);
	return ;
}
