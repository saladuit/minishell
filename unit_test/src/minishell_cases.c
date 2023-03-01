#include <unit_test.h>

Test(minishell_loop, test_commands) {
    // Open a temporary file for writing and write your test commands to it
    FILE *input_file = tmpfile();
    fprintf(input_file, "ls\nexit\n");
    // Rewind the file to the beginning
    rewind(input_file);
    // Redirect standard input to the temporary file
    cr_redirect_stdin_from_file(fileno(input_file));

    // Run your test
    t_minishell sheldon;
    int32_t result = minishell_loop(&sheldon);

    // Assert that the test ran successfully
    cr_assert_eq(result, STOP);

    // Optionally, you can compare the result of the "ls" command
    cr_assert(/* insert your assertion here */);

    // Clean up
    fclose(input_file);
}
