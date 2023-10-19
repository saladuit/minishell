/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_cases.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 09:38:24 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/05 09:38:25 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

/*******************************************************************************/
/*                                Exit_cases */
/*******************************************************************************/

void assert_exit(char **in, bool expected_stop, t_status expected_status)
{
	t_minishell shell;

	bzero(&shell, sizeof(t_minishell));
	ft_exit(in, &shell);
	cr_expect_eq(shell.stop, expected_stop);
	cr_expect_eq(shell.status,
		expected_status,
		"The expression (shell.status): %d == (expected_status):  %d is false)",
		shell.status,
		expected_status);
}

Test(exit, no_argument)
{
	char *in[] = {"exit", NULL, NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_123)
{
	char *in[] = {"exit", "123", NULL};
	assert_exit(in, true, 123);
}

Test(exit, input_minus_one)
{
	char *in[] = {"exit", "-1", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_minus_four)
{
	char *in[] = {"exit", "-4", NULL};
	assert_exit(in, true, 252);
}

Test(exit, input_minus_255)
{
	char *in[] = {"exit", "-255", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_2147483647)
{
	char *in[] = {"exit", "2147483647", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_2147483646)
{
	char *in[] = {"exit", "2147483646", NULL};
	assert_exit(in, true, 254);
}

Test(exit, input_2147483648)
{
	char *in[] = {"exit", "2147483648", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_2147483649)
{
	char *in[] = {"exit", "2147483649", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_2147483650)
{
	char *in[] = {"exit", "2147483650", NULL};
	assert_exit(in, true, 2);
}

Test(exit, input_minus_21474836500000)
{
	char *in[] = {"exit", "-21474836500000", NULL};
	assert_exit(in, true, 224);
}

Test(exit, input_minus_1234)
{
	char *in[] = {"exit", "-1234", NULL};
	assert_exit(in, true, 46);
}

Test(exit, input_21474836500000)
{
	char *in[] = {"exit", "214748365000", NULL};
	assert_exit(in, true, 200);
}

Test(exit, input_256)
{
	char *in[] = {"exit", "256", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_fence)
{
	char *in[] = {"exit", "#", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_semicolon)
{
	char *in[] = {"exit", ";", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_one_with_zeros_in_front)
{
	char *in[] = {"exit", "0001", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_one_with_spaces_in_front)
{
	char *in[] = {"exit", "   1", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_one_with_spaces_and_zeros_in_front)
{
	char *in[] = {"exit", "   0001", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_only_zeros)
{
	char *in[] = {"exit", "0000", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_only_spaces)
{
	char *in[] = {"exit                ", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_very_big_number)
{
	char *in[] = {"exit", "129052340578423590778257728345834758", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_another_big_num)
{
	char *in[] = {"exit", "-9223372036854775808", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_another_big_num_many_ones)
{
	char *in[] = {"exit", "1111111111111111", NULL};
	assert_exit(in, true, 199);
}

Test(exit, input_plus_num)
{
	char *in[] = {"exit", "+5", NULL};
	assert_exit(in, true, 5);
}

Test(exit, input_dash)
{
	char *in[] = {"exit", "-", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_dash_dash)
{
	char *in[] = {"exit", "--", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_twice_dash_dash)
{
	char *in[] = {"exit", "--", "--", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_minus_and_num)
{
	char *in[] = {"exit", "-", "1", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_plus_and_num)
{
	char *in[] = {"exit", "+", "1", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_num_char_and_string)
{
	char *in[] = {"exit", "2a", "dfg", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_float_and_multiple_nums)
{
	char *in[] = {"exit", "2.2", "3", "3", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_exit_exit_num)
{
	char *in[] = {"exit", "exit", "3", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_exit_exit_num_char)
{
	char *in[] = {"exit", "exit", "3a", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_exit_exit_num_num)
{
	char *in[] = {"exit", "exit", "3", "3", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_dollar)
{
	char *in[] = {"exit", "$", NULL};
	assert_exit(in, true, 255);
}

Test(exit, input_empty)
{
	char *in[] = {"exit", "", NULL};
	assert_exit(in, true, 0);
}

Test(exit, input_question_mark)
{
	char *in[] = {"exit", "?", NULL};
	assert_exit(in, true, 1);
}

Test(exit, input_three_times_exit)
{
	char *in[] = {"exit", "exit", "exit", NULL};
	assert_exit(in, true, 255);
}

/*******************************************************************************/
/*                       Exit_cases_with_error_message */
/*******************************************************************************/

void assert_exit_error(
	char **in, bool expected_stop, t_status expected_status, char *expected_message)
{
	t_minishell shell;

	bzero(&shell, sizeof(t_minishell));
	fflush(stderr);
	ft_exit(in, &shell);
	cr_expect_eq(shell.stop, expected_stop);
	cr_expect_eq(shell.status,
		expected_status,
		"The expression (shell.status): %d == (expected_status):  %d is false)",
		shell.status,
		expected_status);
	cr_expect_stderr_eq_str(expected_message);
}

Test(exit, input_alphabetical, .init = redirect_stderr)
{
	char *in[] = {"exit", "abc", NULL};
	assert_exit_error(
		in, true, 255, "Sheldon: exit: abc: numeric argument required\n");
}

Test(exit, input_at_sign, .init = redirect_stderr)
{
	char *in[] = {"exit", "@", NULL};
	assert_exit_error(
		in, true, 255, "Sheldon: exit: @: numeric argument required\n");
}

Test(exit, input_exclamation_mark, .init = redirect_stderr)
{
	char *in[] = {"exit", "!", NULL};
	assert_exit_error(
		in, true, 255, "Sheldon: exit: !: numeric argument required\n");
}

Test(exit, input_num_num, .init = redirect_stderr)
{
	char *in[] = {"exit", "1", "1", NULL};
	assert_exit_error(in, false, 1, "Sheldon: exit: too many arguments\n");
}

/*******************************************************************************/
/*                            Exit_cases_is_pipeline */
/*******************************************************************************/

void assert_exit_is_pipeline(char **in, t_status expected_status)
{
	t_minishell shell;
	pid_t		child;

	bzero(&shell, sizeof(t_minishell));
	shell.is_pipeline = true;
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (child == 0)
	{
		ft_exit(in, &shell);
	}
	else
	{
		waitpid(child, (int *)&shell.status, 0);
		cr_expect_eq(WEXITSTATUS(shell.status),
			expected_status,
			"The expression (shell.status): %d == (expected_status):  %d is "
			"false)",
			WEXITSTATUS(shell.status),
			expected_status);
	}
}

Test(exit, input_child_zero)
{
	char *in[] = {"exit", "0", NULL};
	assert_exit_is_pipeline(in, 0);
}

Test(exit, input_child_one)
{
	char *in[] = {"exit", "1", NULL};
	assert_exit_is_pipeline(in, 1);
}

Test(exit, input_child_big_number)
{
	char *in[] = {"exit", "999", NULL};
	assert_exit_is_pipeline(in, 231);
}
