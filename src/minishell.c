#include <minishell.h>
#include <stdbool.h>
#include <stdio.h>

void	print_tokens(t_list *tokens)
{
	while (tokens != NULL)
	{
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int32_t	minishell(char **envp)
{
	t_list		*abstract_syntax_tree;
	t_list		*tokens;
	char		*command_line; // should be converted into dlist
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	abstract_syntax_tree = NULL;
	command_line = NULL;
	tokens = NULL;
	init_handlers();
	while (true)
	{
		command_line = readline(messages_lookup(PROMPT));
		// printf("Input:\"%s\"\n", command_line);
		if (!command_line)
			exit(0);
		else if (*command_line)
		{
			if (!ft_strncmp(command_line, "exit", 5))
				exit(1);
			printf("lexer\n");
			if (lexer(command_line, &tokens) == ERROR)
				return (EXIT_FAILURE);
			// print_tokens(tokens);
			printf("parser\n");
			if (parser(&abstract_syntax_tree, tokens) == ERROR)
				return (EXIT_FAILURE);
	//		if (expander(command_table) == ERROR)
	//			return (EXIT_FAILURE);
			printf("executor\n");
			if (executor(abstract_syntax_tree, envp) == ERROR) // Fix segfault
				return (EXIT_FAILURE);
			ft_lstclear(&tokens, free);
			// return (EXIT_SUCCESS);
		}
		if (abstract_syntax_tree != NULL)
		{
			clean_abstract_syntax_tree(&abstract_syntax_tree);
			abstract_syntax_tree = NULL;
		}
		free(command_line);
	}
}
