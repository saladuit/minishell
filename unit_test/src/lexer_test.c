#include <unit_test.h>

void	lexer_test(const char input[], const char **expect, const int32_t ret)
{
	int32_t submitted;
	t_list *tokens;
	t_token token;

	tokens = NULL;
	submitted = lexer(input, &tokens);
	while (tokens)
	{
		token = *(t_token *)tokens->content;
	cr_assert(eq(str, token.symbol, (char *)*expect, "Called:\tlexer()\nsymbol:\t%s \nexpected:\t%s\n", token.symbol, *expect));
		tokens = tokens->next;
		expect++;
	}
	cr_assert(submitted == ret);
	ft_lstclear(&tokens, free);
	return ;
}
