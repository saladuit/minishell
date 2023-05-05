/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analyzer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:29:24 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:29:25 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_meta_conventions(const char *command, const char **error_msg);

static bool	find_matching_pipe_error(const char *command,
				const t_tokenerror token_errors[], const char **error_msg)
{
	size_t	i;

	i = 1;
	if (is_pipe(command[i]))
		i++;
	*error_msg = token_errors[i - 1].error_msg;
	return (true);
}

/* Function: check_lexical_conventions
 *
 * Description:
 * Checks whether a given command string adheres
 * to the lexical conventions of the shell.
 * This function uses the compare_command_ignore_spaces function
 * to ignore spaces while
 * comparing the command string against a list of tokens
 * with corresponding error messages.
 * If a match is found, the function sets the exit status
 * with the appropriate error message
 * and returns false, indicating a lexical error.
 * If no matches are found, it returns true,
 * indicating that the command adheres to the lexical conventions.
 *
 * Parameters:
 * const char *command - A null-terminated string
 * representing the command to be checked
 * for adherence to lexical conventions.
 * t_status *exit - A pointer to a t_status variable,
 * which will be set with the appropriate error message
 * if a lexical error is detected.
 *
 * Returns:
 * true if the command adheres to the lexical conventions,
 * and false if a lexical error is detected.
 * If a lexical error is detected,
 * the exit status will be set with the appropriate error message.
 */

static bool	find_matching_error(const char *command,
		const t_tokenerror token_errors[], const char **error_msg)
{
	size_t	i;

	i = 0;
	if (is_pipe(*command))
		return (find_matching_pipe_error(command, token_errors, error_msg));
	if ((is_metas(command) || is_meta(command[0])) && ft_strlen(command) > 2)
		i = 7;
	while (token_errors[i].token != NULL)
	{
		if (compare_command_ignore_spaces(command,
				token_errors[i].token) == NOT_FOUND)
		{
			*error_msg = token_errors[i].error_msg;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_meta_conventions(const char *command, const char **error_msg)
{
	const t_tokenerror		token_errors[] = {
	{"|", "|"},
	{"||", "||"},
	{"<", "newline"},
	{"<<", "newline"},
	{">", "newline"},
	{">>", "newline"},
	{NULL, NULL}};

	if (find_matching_error(command, token_errors, error_msg))
		return (false);
	return (true);
}

static bool	check_lexical_conventions_iterate(const char *command,
			const t_tokenerror *token_errors, t_status *exit)
{
	const char	*error_msg;

	error_msg = NULL;
	if (find_matching_error(command, token_errors, &error_msg))
	{
		*exit = message_general_error(E_UNEXPECTED_TOKEN, error_msg);
		return (false);
	}
	return (true);
}

bool	check_lexical_conventions(const char *command, t_status *exit)
{
	const t_tokenerror		token_errors[] = {
	{"|", "|"},
	{"||", "||"},
	{"<", "newline"},
	{"<<", "newline"},
	{">", "newline"},
	{">>", "newline"},
	{"!", "newline"},
	{">> >", ">"},
	{"<< <", "<"},
	{"< <", "<"},
	{"> >", ">"},
	{"<< <<", "<<"},
	{">> >>", ">>"},
	{"<< >", ">"},
	{">> <", "<"},
	{NULL, NULL}};

	return (check_lexical_conventions_iterate(command, token_errors, exit));
}
