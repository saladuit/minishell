/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   lexer_test.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/16 11:16:10 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/16 11:33:10 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

void	lexer_test(const char input[], const char **expect, const int32_t ret)
{
	int32_t submitted;
	t_list *tokens;

	tokens = NULL;
	submitted = lexer(input, &tokens);
	while (tokens)
	{
	cr_assert(tokens->content->symbol == expected,
			"Called:\nlexer()\nsymbol:\t%s \nexpected:\t%d\n",
			tokens->content->symbol,
			*expected);
		tokens = tokens->next;
	}
	cr_assert(submitted == expected);
	ft_lstclear(input, free);
	return ;
}
