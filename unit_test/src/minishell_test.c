/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minishell_test.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/07/16 21:12:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/16 10:53:19 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

void	minishell_test(const char *envp[], const size_t count, int32_t expected)
{
	int32_t submitted;
	char	*input;

	input = ft_joinmatrix(envp, count);
	submitted = minishell((char **)envp);
	cr_assert(submitted == expected,
			"Called:\tminishell()\nenvp:\t\t%s\n\
			expected:\t%d \nsubmitted:\t%d\n",
			input,
			expected,
			submitted);
	free(input);
	return ;
}
