#include <unit_test.h>

void	lexer_test(const char input[], const char **expect, const int32_t ret)
{
	int32_t	submitted;
	t_list	*tokens;
	char	*token;

	tokens = NULL;
	submitted = lexer(input, &tokens);
	while (tokens)
	{
		token = (char *)tokens->content;
	cr_assert(eq(str, token, (char *)*expect, "Called:\tlexer()\nsymbol:\t%s \nexpected:\t%s\n", token, *expect));
		tokens = tokens->next;
		expect++;
	}
	cr_assert(submitted == ret);
	ft_lstclear(&tokens, free);
	return ;
}
