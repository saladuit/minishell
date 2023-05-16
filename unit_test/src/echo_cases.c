/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_cases.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:37:57 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:37:58 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                          	    Echo_cases                                 */
/*******************************************************************************/

void	assert_echo_case(char **input, char *expected)
{
	t_minishell	shell;

	bzero(&shell, sizeof(shell));
	ft_echo(input, &shell);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

TestSuite(echo, .init=redirect_stdout);

Test(echo, input_empty)
{
	char		*input[] = {"echo", NULL};
	char		*expected = "\n";
	assert_echo_case(input, expected);
}

Test(echo, input_empty_with_flag)
{
	char		*input[] = {"echo", "-n", NULL};
	char		*expected = "";
	assert_echo_case(input, expected);
}

Test(echo, input_string_with_multiple_flags)
{
	char		*input[] = {"echo", "-n", "-n", "-n", "test", NULL};
	char		*expected = "test";
	assert_echo_case(input, expected);
}

Test(echo, input_empty_with_two_flags)
{
	char		*input[] = {"echo", "-n", "-n", NULL};
	char		*expected = "";
	assert_echo_case(input, expected);
}

Test(echo, input_hello_world)
{
	char		*input[] = {"echo", "hello world", NULL};
	char		*expected = "hello world\n";
	assert_echo_case(input, expected);
}

Test(echo, input_two_back_slashes)
{
	char		*input[] = {"echo", "\\\\", NULL};
	char		*expected = "\\\\\n";
	assert_echo_case(input, expected);
}

Test(echo, input_one_back_slashes)
{
	char		*input[] = {"echo", "\\", NULL};
	char		*expected = "\\\n";
	assert_echo_case(input, expected);
}

Test(echo, input_two_single_quotes_with_space_inside)
{
	char		*input[] = {"echo", " ", NULL};
	char		*expected = " \n";
	assert_echo_case(input, expected);
}

Test(echo, input_space)
{
	char		*input[] = {"echo", " ", NULL};
	char		*expected = " \n";
	assert_echo_case(input, expected);
}

Test(echo, input_txt_empty_txt_empty_txt)
{
	char		*input[] = {"echo", "txt", "", "txt", "", "test", NULL};
	char		*expected = " \n";
	assert_echo_case(input, expected);
}

Test(echo, input_newline)
{
	char		*input[] = {"echo", "\n", NULL};
	char		*expected = "\n\n";
	assert_echo_case(input, expected);
}

Test(echo, input_very_long_string)
{
	char		*input[] = {"echo", "a very long string with lots of characters and spaces... ", NULL};
	char		*expected = "a very long string with lots of characters and spaces... \n";
	assert_echo_case(input, expected);
}

Test(echo, input_special_chars)
{
	char		*input[] = {"echo", "!@#$%^&*()", NULL};
	char		*expected = "!@#$%^&*()\n";
	assert_echo_case(input, expected);
}

Test(echo, input_multiple_args)
{
	char		*input[] = {"echo", "multiple", "args", NULL};
	char		*expected = "multiple args\n";
	assert_echo_case(input, expected);
}
