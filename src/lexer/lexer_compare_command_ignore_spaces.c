/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_compare_command_ignore_spaces.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 13:14:22 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 13:14:23 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	compare_command_ignore_spaces(const char *command, const char *cmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (command[i] && cmp[j])
	{
		if (command[i] != SPACE && cmp[j] == SPACE)
			j++;
		if (command[i] == SPACE && cmp[j] != SPACE)
			i++;
		if (command[i++] != cmp[j++])
			return (false);
	}
	while (command[i])
		if (command[i++] != SPACE)
			return (false);
	return (true);
}
