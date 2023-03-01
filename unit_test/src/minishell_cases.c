#include <unit_test.h>

Test(minishell_loop, test_commands)
{
	FILE		*input_file;
	t_minishell	sheldon;
	int32_t		result;

	// Open a temporary file for writing and write your test commands to it
	input_file = tmpfile();
	fprintf(input_file, "ls\nexit\n");
	// Rewind the file to the beginning
	rewind(input_file);
	// Redirect standard input to the temporary file
	cr_redirect_stdin_from_file(fileno(input_file));
	// Run your test
	result = minishell_loop(&sheldon);
	// Assert that the test ran successfully
	cr_assert_eq(result, STOP);
	// Optionally, you can compare the result of the "ls" command
	cr_assert(/* insert your assertion here */);
	// Clean up
	fclose(input_file);
}
