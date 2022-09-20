#include <unit_test.h>

void	get_command_test(const char input[], const char *expect[])
{
	t_list		*tokens;
	t_command	*command;

	command = NULL;
	tokens = NULL;
	lexer(input, &tokens);
	command = get_command(&tokens);
	while (*expect)
	{
		cr_expect(eq(str, *command->arguments, (char *)(*expect)));
		command->arguments++;
		expect++;
	}
	free(command->arguments);
	free(command);
	ft_lstclear(&tokens, free);
}

//void	get_redir_test(const char input[], const char *expect[])
//{
//	t_list		*tokens;
//	t_command	*command;
//	char 		*token;
//
//	(void)expect;
//	tokens = NULL;
//	command = NULL;
//	lexer(input, &tokens);
//	command = get_command(&tokens);
//	while (*expect)
//	{
//		token = command->redirs->content;	
//		cr_expect(eq(str, token, (char *)(*expect)));
//		command->redirs = command->redirs->next;
//		expect++;
//	}
//	cr_assert(zero(ptr, command->redirs)); 
//	ft_lstclear(&command->redirs, free);
//	free(command);
//	ft_lstclear(&tokens, free);
//}
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
