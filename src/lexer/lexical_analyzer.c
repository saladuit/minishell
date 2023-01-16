#include <minishell.h>

int32_t	check_validity(t_list *tokens)
{
	if (!ft_strncmp(tokens->content, "|", 2))
		return (pipe_check(tokens));
	else if (!ft_strncmp(tokens->content, "<", 2))
		return (input_check(tokens));
	else if (!ft_strncmp(tokens->content, ">", 2))
		return (output_check(tokens));
	else if (!ft_strncmp(tokens->content, ">>", 3))
		return (append_check(tokens));
	else if (!ft_strncmp(tokens->content, "<<", 3))
		return (heredoc_check(tokens));
	return (0);
}

void	print_syntax_error(t_list *tokens)
{
	if (!tokens)
		printf("Minishell: syntax error near unexpected token `newline\'\n");
	else
		printf("Minishell: syntax error near unexpected token `%s\'\n",
			tokens->content);
}

// void	print_tokens(t_list *tokens)
// {
// 	t_list	*tmp;

// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		printf("[%s]\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }

int32_t	analyzer(t_list *tokens)
{
	// print_tokens(tokens);
	if (!ft_strncmp(tokens->content, "|", 2))
		return (printf("Minishell: syntax error near unexpected token `|\'\n"),
			1);
	while (tokens)
	{
		if (is_tokenchar(tokens->content))
			if (check_validity(tokens))
				return (print_syntax_error(tokens->next), 1);
		tokens = tokens->next;
	}
	return (0);
}
