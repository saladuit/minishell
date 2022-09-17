#include <unit_test.h>

void	get_command_test(const char input[], const char *expect[])
{
	t_list		*tokens;
	t_command	*command;
	char 		*token;

	(void)expect;
	tokens = NULL;
	command = NULL;
	lexer(input, &tokens);
	command = get_command(&tokens);
	while (*expect)
	{
		token = command->tokens->content;	
		cr_assert(eq(str, token, (char *)(*expect)));
		command->tokens = command->tokens->next;
		expect++;
	}
	ft_lstclear(&command->tokens, free);
	free(command);
	ft_lstclear(&tokens, free);
}
//void	parser_test(const char input[], const char *expect[], const int32_t ret)
//{
//	int32_t	submitted;
//	t_list	*tokens;
//	t_list *ast;
//
//	tokens = NULL;
//	lexer(input, &tokens);
//	subimmted = parser(&ast, tokens);
//	while (tokens)
//	{
//		ast->content->
//		cr_assert(eq(str, token, (char *)*expect, "Called:\nparser()\nsymbol:\t%s \nexpected:\t%s\n", token, *expect));
//		tokens = tokens->next;
//		expect++;
//	}
//	cr_assert(submitted == ret);
//	ft_lstclear(&tokens, free);
//	return ;
//}
