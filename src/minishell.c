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
// remove before finishing project (for debugging)
void	print_ast(t_list *ast)
{
	t_command_table	*table;
	t_list			*com_lst;
	t_command		*command;
	t_list			*args_lst;
	t_list			*redir_lst;
	t_list			*ast_lst;
	t_redir			*tmp_redir;

	ast_lst = ast;
	while (ast_lst)
	{
		table = (t_command_table *)ast_lst->content;
		com_lst = table->commands;
		printf("ast [%p]:\n", ast_lst);
		printf("|  Table [%p]:\n", table);
		printf("|  |  Command count: %i\n", table->command_count);
		while (com_lst)
		{
			command = (t_command *)com_lst->content;
			printf("|  |  Command:\n");
			if (command)
			{
				args_lst = command->arguments;
				printf("|  |  |  Arguments:\n");
				while (args_lst)
				{
					printf("|  |  |  |  [%p]->[%s]\n", args_lst, args_lst->content);
					args_lst = args_lst->next;
				}
				redir_lst = command->redirs;
				printf("|  |  |  Redirects:\n");
				while (redir_lst)
				{
					tmp_redir = redir_lst->content;
					printf("|  |  |  |  [%p]->[%s] - [%i]\n", tmp_redir, tmp_redir->filename, tmp_redir->type);
					redir_lst = redir_lst->next;
				}
			}
			com_lst = com_lst->next;
		}
		ast_lst = ast_lst->next;
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
	// print_tokens(sheldon->tokens); // debug line
	if (!sheldon->tokens)
		return (SUCCESS);
	if (analyzer(sheldon->tokens))
	{
		ft_lstclear(&sheldon->tokens, free);
		return (EXIT_FAILURE);
	}
	sheldon->ast = parser(sheldon->tokens);
	// print_ast(sheldon->ast); // debug line
	ft_lstclear(&sheldon->tokens, free);
	if (g_exitcode == 300)
	{
		g_exitcode = 0;
		return (SUCCESS);
	}
	// printf("expanding\n"); // debug line
	// print_ast(sheldon->ast); // debug line
	expander(sheldon);
	g_exitcode = 0;
	// printf("executor\n"); // debug line
	g_exitcode = executor(sheldon);
	free(command_line);
	return (EXIT_SUCCESS);
}
