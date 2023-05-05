/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_cases.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:39:09 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:39:11 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                            heredoc_basic_cases                              */
/*******************************************************************************/

void	assert_heredoc_basic(char *delimiter, int32_t expected_output)
{
	int32_t	pipe_fd[2];
	int32_t	output;

	bzero(&pipe_fd, sizeof(pipe_fd));
	output = here_doc(delimiter, pipe_fd[WRITE_END]);
	cr_assert_eq(output, expected_output);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

Test(heredoc, null_delimiter)
{
	assert_heredoc_basic(NULL, ERROR);
}

Test(heredoc, empty_delimiter)
{
	assert_heredoc_basic("", ERROR);
}

/*******************************************************************************/
/*                               heredoc_cases                                 */
/*******************************************************************************/

void	assert_heredoc(char *delimiter, char *input, char *expected_output)
{
	int		pipe_fd[2];
	char 	buf[1024];
	ssize_t	num_bytes;

	cr_assert(pipe(pipe_fd) == SUCCESS, "%s", strerror(errno));
	write(pipe_fd[WRITE_END], input, strlen(input));
	dup2(pipe_fd[READ_END], STDIN_FILENO);
	here_doc(delimiter, pipe_fd[WRITE_END]);
	num_bytes = read(pipe_fd[READ_END], buf, sizeof(buf));
	buf[num_bytes] = '\0';
	cr_assert_str_eq(buf, expected_output);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}

Test(heredoc, one_line)
{
	char	*delimiter = "EOF";
	char	*input = "line 1\nEOF\n";
	char	*expected_output = "line 1\n";
	assert_heredoc(delimiter, input, expected_output);
}

Test(heredoc, two_lines)
{
	char	*delimiter = "EOF";
	char	*input = "line 1\nline 2\nEOF\n";
	char	*expected_output = "line 1\nline 2\n";
	assert_heredoc(delimiter, input, expected_output);
}
