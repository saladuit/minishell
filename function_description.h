/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_description.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 13:47:45 by dritsema      #+#    #+#                 */
/*   Updated: 2022/09/13 14:05:31 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_DESCRIPTION_H
# define FUNCTION_DESCRIPTION_H


/** @brief readline will read a line from the terminal and return it, using
		prompt as a prompt.  If prompt is NULL or the empty string, no
		prompt is issued.  The line returned is allocated with malloc(3);
		the caller must free it when finished.
 *
 * @param prompt
 * @return readline returns the line read. A blank line returns
		the empty string.  If EOF is encountered and the line is empty,
		NULL is returned.  If an EOF is read with
		a non-empty line, it is treated as a newline.*/
char	*readline(const char *prompt);

/**
 * @brief clears history?
 *
 */
extern void rl_clear_history PARAMS((void));

// Tell the update functions that we have moved onto a new (empty) line,
// usually after outputting a newline.
extern int rl_on_new_line PARAMS((void));

extern void rl_replace_line PARAMS((const char *, int));
// Change what's displayed on the screen to reflect the current
// contents of rl_line_buffer.
extern void rl_redisplay PARAMS((void));

/* Place STRING at the end of the history list.
   The associated data field (if any) is set to NULL. */
extern void add_history PARAMS((const char *));

#endif // FUNCTION_DESCRIPTION_H
