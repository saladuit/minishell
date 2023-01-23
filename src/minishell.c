#include <minishell.h>

// print the tokens (for debugging)
void	print_tokens(t_list *tokens)
{
	printf("tokens:\n");
	while (tokens)
	{
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
}

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(t_minishell *sheldon)
{
	char		*command_line;

	setup_signals(SREADLINE);
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line && printf("exit"))
		exit(E_GENERAL);
	if (!*command_line)
		return (SUCCESS);
	add_history(command_line);
	lexer(command_line, &sheldon->tokens);
	if (!sheldon->tokens)
		return (SUCCESS);
	if (analyzer(sheldon->tokens))
	{
		ft_lstclear(&sheldon->tokens, free);
		return (EXIT_FAILURE);
	}
	sheldon->ast = parser(sheldon->tokens);
	if (g_exitcode == 300)
	{
		g_exitcode = 0;
		return (SUCCESS);
	}
	ft_lstclear(&sheldon->tokens, free);
	expander(sheldon);
	g_exitcode = 0;
	g_exitcode = executor(sheldon);
	free(command_line);
	return (EXIT_SUCCESS);
}
