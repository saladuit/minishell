#include <minishell.h>

static bool	find_matching_pipe_error(const char *command,
										const t_tokenerror token_errors[], const char **error_msg)
{
	size_t	i;

	i = 1;
	if (is_pipe(command[i]))
		i++;
	*error_msg = token_errors[i + 4].error_msg;
	return (true);
}

/*
 * Function: compare_command_ignore_spaces
 *
 * Description:
 * Compares two command strings,
 * ignoring any spaces that may be present within the commands. 
 * This function is useful for comparing command strings 
 * that may contain extra spaces,
 * which should be considered equivalent for the purpose of comparison.
 * 
 * Parameters:
 * const char *command - A null-terminated string 
 * representing the command to be compared.
 * char *cmp - A null-terminated string 
 * representing the reference command to be compared against.
 *
 * Returns:
 * 
 * NOT_FOUND if the commands are different or 
 * if there is a mismatch after ignoring spaces. 
 * Otherwise, it returns 1.
 */

static size_t strlen_ignore_spaces(const char *str)
{
	size_t	i;
	size_t	len;

	if (!str || !str[0])
		return (0);
	i = 0;
	len  = 0;
	while (str[i])
		if (!ft_iswhitespace(str[i++]))
			len++;
	return (len);
}

static int	compare_command_ignore_spaces(const char *command, const char *cmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (strlen_ignore_spaces(command) != strlen_ignore_spaces(cmp))
		return (false);
	while (command[i] && cmp[j])
	{
		if (command[i] != ' ' && cmp[j] == ' ')
			j++;
		if (command[i] == ' ' && cmp[j] != ' ')
			i++;
		if (command[i++] != cmp[j++])
			return (false);
	}
	while (command[i])
		if (command[i++] != ' ')
			return (false);
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
		const t_tokenerror token_errors[], const char **error_msg, t_lexer *lex)
{
	size_t	i;

	i = 0;
	if (lex->token_count > 0 && !lex->meta_conv)
		i = 5;
	if (is_pipe(*command) && lex->token_count == 0)
		return (find_matching_pipe_error(command, token_errors, error_msg));
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

bool	check_meta_conventions(const char *command, const char **error_msg, t_lexer *lex)
{
	lex->meta_conv = true;
	if (lex->meta_count == 2)
		return (false);
	const t_tokenerror		token_errors[] = {
			{"|", "|"},
			{"||", "||"},
			{"<", "<"},
			{"<<", "<<"},
			{">", ">"},
			{">>", ">>"},
			{NULL, NULL}};

	if (find_matching_error(command, token_errors, error_msg, lex))
		return (false);
	return (true);
}

bool	check_lexical_conventions(const char *command, t_status *exit, t_lexer *lex)
{
	const char				*error_msg;
	const t_tokenerror		token_errors[] = {
	{"!", "newline"},
	{">> >", ">"},
	{"<< >", ">"},
	{">> <", "<"},
	{"<< <", "<"},
	{"|", "|"},
	{"||", "||"},
	{"<", "newline"},
	{"<<", "newline"},
	{">", "newline"},
	{">>", "newline"},
	{NULL, NULL}};

	error_msg = NULL;
	if (find_matching_error(command, token_errors, &error_msg, lex))
	{
		if (lex->token_count == 0)
			*exit = message_general_error(E_UNEXPECTED_TOKEN, error_msg);
		return (false);
	}
	return (true);
}

bool	control_conventions(const char *command, t_status *exit, t_lexer *lex, const char **error_msg)
{
	if (lex->meta_count > 1)
		return (check_meta_conventions(command, error_msg, lex));
	else if (lex->token_count > 0)
		return (check_lexical_conventions(command, exit, lex));
	else
		return (true);
}
