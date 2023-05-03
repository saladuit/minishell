#include <unit_test.h>

/*******************************************************************************/
/*                            heredoc_basic_cases                              */
/*******************************************************************************/

void	assert_heredoc_basic(char *delimiter, int32_t expected_output)
{
	int32_t	output_fd;

	output_fd = here_doc(delimiter);
	cr_assert_eq(output_fd, expected_output);
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
	int		output_fd;
	char 	buf[1024];
	ssize_t	num_bytes;

	cr_assert(pipe(pipe_fd) == SUCCESS, "%s", strerror(errno));
	write(pipe_fd[1], input, strlen(input));
	dup2(pipe_fd[0], STDIN_FILENO);
	output_fd = here_doc(delimiter);
	num_bytes = read(output_fd, buf, sizeof(buf));
	buf[num_bytes] = '\0';
	cr_assert_str_eq(buf, expected_output);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(output_fd);
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
