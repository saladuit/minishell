#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <criterion/new/assert.h>
#include <unit_test.h>

#define MINISHELL_TEST(test_case, command_line) \
    Test(minishell, test_case) { \
        assert_minishell(command_line, #test_case); \
    }


/*******************************************************************************/
/*                           Directory_names                                   */
/*******************************************************************************/
extern char **environ;

void redirect_stdfds(void)
{
    cr_redirect_stdout();
    cr_redirect_stdin();
    cr_redirect_stderr();
}

int32_t	minishell_loop(t_minishell *sheldon);

TestSuite(minishell, .init=redirect_stdfds, .timeout=4);

static int read_from_file(void *cookie, void *buffer, size_t *size)
{
    FILE *file = (FILE *)cookie;
    size_t read_size = fread(buffer, 1, *size, file);
    *size = read_size;
    return 0;
}
void assert_minishell(char *command_line, char *case_name)
{
    char *txt_file_path;
    char *system_call;
    char *minishell_command;
    FILE *f_stdin = cr_get_redirected_stdin();

    txt_file_path = calloc(strlen(case_name) + 27, sizeof(char));
    sprintf(txt_file_path, "build/%s.txt", case_name);

    system_call = calloc(strlen(txt_file_path) + strlen(command_line) + 15, sizeof(char));
    sprintf(system_call, "bash -c \'%s\' >| %s", command_line, txt_file_path);

    minishell_command = calloc(strlen(command_line)+ 5, sizeof(char));
    sprintf(minishell_command, "%s\nEOF", command_line);

    struct cr_stream actual = {
        .cookie = cr_get_redirected_stdout(),
        .read   = read_from_file,
    };

    system(system_call);
    struct cr_stream expected = {
        .cookie = fopen(txt_file_path, "r"),
        .read   = read_from_file,
    };
    cr_stream_init(&expected);
    cr_stream_init(&actual);
	fputs(minishell_command, f_stdin);
    fclose(f_stdin);
    minishell(environ);
    fflush(stdout);
    fflush(stdin);
    fflush(stderr);

    cr_assert(eq(stream, expected, actual));
    fclose(expected.cookie);
    free(system_call);
    free(txt_file_path);
    free(minishell_command);
}

/*******************************************************************************/
/*                              execution                                    */
/*******************************************************************************/

MINISHELL_TEST(execution_empty_string, "\'\'");
MINISHELL_TEST(execution_ls_expansion_2, "ls $whitespace_center$whitespace_center\n");
// MINISHELL_TEST(execution_pipeline_command_not_found, "echo hi > foo | asd\ncat foo\n");
// MINISHELL_TEST(execution_no_PATH, "unset PATH\ncat");
// MINISHELL_TEST(execution_env_expansion_splitting_space_separator, "export a=\" \"\necho foo$a\"bar\"");
// MINISHELL_TEST(execution_garbage, "/usr/bin/foo");
// MINISHELL_TEST(execution_basic, "ls .\nl\"s\" .\nl\'s\' .\nexport s=\" s\"\nl$s .\nexport s=\"s\"\nl$s .\nlsX .");
// MINISHELL_TEST(execution_leading_whitespace, "a");
// MINISHELL_TEST(execution_space_in_string, "\' \'");
// MINISHELL_TEST(execution_env_expansion_splitting_space_right, "export a=\"b \"\necho foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_spaces_everywhere, "export a=\" b c \"\necho foo $a bar");
// MINISHELL_TEST(execution_pipeline_no_PATH, "unset PATH\necho hi > foo | asd\ncat foo");
// MINISHELL_TEST(execution_ls, "ls");
// MINISHELL_TEST(execution_env_expansion_splitting_space, "export a=\" \"\necho foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_empty, "export a=\"\"\nls foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_left_space_separator, "export a=\" b\"\necho foo$a\"bar\"");
// MINISHELL_TEST(execution_space, "");
// MINISHELL_TEST(execution_env_expansion_splitting_space_left, "export a=\" b\"\necho foo $a bar");
// MINISHELL_TEST(execution_trailing_whitespace, "a");
// MINISHELL_TEST(execution_whitespace_center, "$whitespace_center");
// MINISHELL_TEST(execution_pipeline_expansion, "export a=\"| ls\"\n$a");
// MINISHELL_TEST(execution_ls_expansion, "ls $whitespace_center");
// MINISHELL_TEST(execution_command_not_found, "asd");
// MINISHELL_TEST(execution_command_not_found_and_no_such_file_or_directory, "asd\n/asd\ncat foo");


/*******************************************************************************/
/*                                   echo                                      */
/*******************************************************************************/

// MINISHELL_TEST(echo, "echo");
// MINISHELL_TEST(echo_basic, "echo a");
// MINISHELL_TEST(echo_double, "echo a b");
// MINISHELL_TEST(echo_n_option_several, "echo -n -n a -n -n");
// MINISHELL_TEST(echo_n_option_nn, "echo -nn a -nn");
// MINISHELL_TEST(echo_n_option_nan, "echo -nan a -nan");
// MINISHELL_TEST(echo_n_option_na, "echo -na a -na");
// MINISHELL_TEST(echo_n_option_ana, "echo -ana a -ana");
// MINISHELL_TEST(echo_n_option_an, "echo -an a -an");
// MINISHELL_TEST(echo_n_option_first, "echo -n a\necho -n a b");
// MINISHELL_TEST(echo_n_option_last, "echo a -n\necho a b -n");
// MINISHELL_TEST(echo_expansion, "echo $whitespace_center");
//
//
// /*******************************************************************************/
// /*                                  pwd                                       */
// /*******************************************************************************/
//
// MINISHELL_TEST(pwd, "pwd");
// MINISHELL_TEST(pwd_old, "env | grep OLDPWD\nexport | grep OLDPWD\n\ncd .\nenv | grep OLDPWD\nexport | grep OLDPWD");
// MINISHELL_TEST(pwd_removed_dir, "mkdir test\ncd test\nrmdir /tmp/test\npwd");
// MINISHELL_TEST(pwd_hoi, "pwd hoi");
//
//
// /*******************************************************************************/
// /*                               exit_status                                   */
// /*******************************************************************************/
//
// MINISHELL_TEST(exit_status_quoted, "export a=\"$?\"\nrm .\necho $a\n\nexport b=\'$?\'\nrm .\necho $b");
// MINISHELL_TEST(exit_status_basic, "echo hello\necho $?");
// MINISHELL_TEST(exit_status_trailing, "echo $?a\necho $??\necho $?$?\necho $?$?a");
// MINISHELL_TEST(exit_status_error, "rm .\necho $?");
//
//
// /*******************************************************************************/
// /*                                  cat                                       */
// /*******************************************************************************/
//
// MINISHELL_TEST(cat_me_relative, "cat ../sample-txt/cat-me.txt");
// MINISHELL_TEST(cat_me, "cat sample-txt/cat-me.txt | grep cat | wc -w");
//
//
// /*******************************************************************************/
// /*                              appends                                     */
// /*******************************************************************************/
//
// MINISHELL_TEST(create_files, "pwd >> a >> b >> b\ncat a\ncat b\nls");
//
//
// /*******************************************************************************/
// /*                                    misc                                      */
// /*******************************************************************************/
//
// // MINISHELL_TEST(argv_string_concatenation, "/\'Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv\' \'foo\'bar\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"bar\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\" \"bar\"\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"\"bar\"\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\' \'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\'\'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"\'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\'\"bar\"");
// // MINISHELL_TEST(nothing, "");
// MINISHELL_TEST(ls, "ls\nls nonexistent\nls -la /");
// MINISHELL_TEST(envp, "/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/envp | sort");
// MINISHELL_TEST(space, "");
//
//
// /*******************************************************************************/
// /*                              nested_minishell                                */
// /*******************************************************************************/
//
// // MINISHELL_TEST(ls, "$minishell_path\nls");
//
//
// /*******************************************************************************/
// /*                                  export                                     */
// /*******************************************************************************/
//
// MINISHELL_TEST(export_overwrite_with_no_value, "export a=\"x\"\necho $a\nexport a=\necho $a");
// MINISHELL_TEST(export_exports_are_unquoted, "export a=\">\"\n$a b");
// MINISHELL_TEST(export_export_multiple_same, "export a=b a=b\nexport | sort");
// MINISHELL_TEST(export_multiple_equals, "export FOO=a=b\nexport | grep FOO");
// MINISHELL_TEST(export_number_as_second_character, "export a1=foo");
// MINISHELL_TEST(export_basic, "export foo=\"bar\"\necho $foo");
// MINISHELL_TEST(export_valid_and_not_valid_identifier, "export 1 a=b 2\nexport | sort");
// MINISHELL_TEST(export_export_multiple, "export a=b x=y\nexport | sort");
// MINISHELL_TEST(export_single_character, "export a=foo");
// MINISHELL_TEST(export_copying, "export a=foo\nexport b=$a\necho $b\n\nexport a=bar\necho $a\necho $b");
// MINISHELL_TEST(export_overwrite_with_no_equals, "export a=\"x\"\necho $a\nexport a\necho $a");
// MINISHELL_TEST(export_with_value, "export FOO=BAR\nexport | grep FOO");
// MINISHELL_TEST(export_export_sorted, "export | sort");
// MINISHELL_TEST(export_no_equals, "export FOO\nexport | grep FOO");
// MINISHELL_TEST(export_no_value, "export FOO=\nexport | grep FOO");
// MINISHELL_TEST(export_overwrite, "export a=\"x\"\necho $a\nexport a=\"y\"\necho $a");
// MINISHELL_TEST(export_set_export, "export foo=\"bar\"");
// MINISHELL_TEST(export_invalid_1, "export _@=foo");
// MINISHELL_TEST(export_invalid_2, "export 1=foo");
//
// /*******************************************************************************/
// /*                                  pipes                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(pipes_ls_grep_t, "ls | grep t");
// MINISHELL_TEST(pipes_redir_and_pipe, "ls > foo\nsort < foo | grep t\nrm foo");
// MINISHELL_TEST(pipes_grep_ls, "ls / | grep bin");
// MINISHELL_TEST(pipes_eagain_resource_temporarily_unavailable, "pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd | pwd");
// MINISHELL_TEST(pipes_ls_cat, "ls | cat");
//
//
// /*******************************************************************************/
// /*                                  env                                       */
// /*******************************************************************************/
//
// MINISHELL_TEST(env_redirection_in_env, "export a=\">\"\necho x $a y");
// MINISHELL_TEST(env_echo_var, "echo $no_whitespace");
// MINISHELL_TEST(env_env_sorted, "env | sort");
// MINISHELL_TEST(env_no_such_file_or_directory, "$USER");
// MINISHELL_TEST(env_with_value, "export FOO=BAR\nenv | grep FOO");
// MINISHELL_TEST(env_no_equals, "export FOO\nenv | grep FOO");
// MINISHELL_TEST(env_no_value, "export FOO=\nenv | grep FOO");
// MINISHELL_TEST(env_env_in_env, "export a=\'$empty\'\n$a");
// MINISHELL_TEST(env_dollar, "echo $");
//
//
// /*******************************************************************************/
// /*                                  echo                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(echo_15, "echo 1$USER-");
// MINISHELL_TEST(echo_9, "echo $11");
// MINISHELL_TEST(echo_13, "echo $xa");
// MINISHELL_TEST(echo_6, "echo $_x");
// MINISHELL_TEST(echo_12, "echo $x_");
// MINISHELL_TEST(echo_10, "echo $@1");
// MINISHELL_TEST(echo_2, "echo $?$?");
// MINISHELL_TEST(echo_18, "echo @ b");
// MINISHELL_TEST(echo_1, "echo $?");
// MINISHELL_TEST(echo_11, "echo $ 1");
// MINISHELL_TEST(echo_8, "echo $1x");
// MINISHELL_TEST(echo_4, "echo $?foo");
// MINISHELL_TEST(echo_7, "echo $ax");
// MINISHELL_TEST(echo_16, "echo 1$USER$USER-");
// MINISHELL_TEST(echo_5, "echo $");
// MINISHELL_TEST(echo_14, "echo $x1");
// MINISHELL_TEST(echo_3, "echo foo$?");
// MINISHELL_TEST(echo_17, "echo a b");
//
//
// /*******************************************************************************/
// /*                                  exit                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(exit, "exit");
// MINISHELL_TEST(exit_0, "exit 0");
// MINISHELL_TEST(exit_too_many_args_string_string, "p\nexit a b");
// MINISHELL_TEST(exit_1, "exit 1");
// MINISHELL_TEST(exit_too_many_args_number_string, "p\nexit 4 a");
// MINISHELL_TEST(exit_too_many_args_string_number, "p\nexit a 2");
// MINISHELL_TEST(exit_letter, "exit a");
// MINISHELL_TEST(exit_too_many_args_number_number, "p\nexit 4 2");
// MINISHELL_TEST(exit_garbage, "exit -18abc");
// MINISHELL_TEST(exit_12345678, "exit 12345678");
// MINISHELL_TEST(exit_after_error, "rm .\nexit");
// MINISHELL_TEST(exit_after_error_2, "p\nexit");
// MINISHELL_TEST(exit_minus_one, "exit -1");
// MINISHELL_TEST(exit_99999999, "exit 9999999999999");
//
// /*******************************************************************************/
// /*                              redirections                                  */
// /*******************************************************************************/
//
// MINISHELL_TEST(redirect_redirection_in, "ls > abc\n< abc sort\nrm abc");
// MINISHELL_TEST(redirect_last_input_is_read, "echo a > a\necho b > b\necho c > c\necho d > d\n\n< a < b cat < c < d");
// MINISHELL_TEST(redirect_cat_redirection_created_file, "ls > abc\ncat abc\nrm abc");
// MINISHELL_TEST(redirect_create_files, "pwd > a > b\ncat a\ncat b\nls\nrm a\nrm b");
// MINISHELL_TEST(redirect_last_output_is_written_to, "> a > b echo x > c > d\necho y\ncat a\necho y\ncat b\necho y\ncat c\necho y\ncat d\necho y");
//
//
// /*******************************************************************************/
// /*                                  regular                                     */
// /*******************************************************************************/
//
// MINISHELL_TEST(regular_15, "echo a > \'\'$whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_9, "echo a > \"foo\"$whitespace_right\nrm foowhitespace");
// MINISHELL_TEST(regular_13, "echo a > \'$foo\'\nrm $foo");
// MINISHELL_TEST(regular_6, "echo a > $whitespace_right \"foo\"\nrm whitespace");
// MINISHELL_TEST(regular_21, "< x echo");
// MINISHELL_TEST(regular_12, "echo a > \"c\"$empty\"d\"\nrm cd");
// MINISHELL_TEST(regular_10, "echo a > \"c\"$food\nrm c");
// MINISHELL_TEST(regular_2, "echo a > \"foo\" $whitespace_left\nrm foo");
// MINISHELL_TEST(regular_18, "echo a > \"foo\"\"$whitespace_left\"\nrm \"foo whitespace\"");
// MINISHELL_TEST(regular_1, "echo a > $whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_22, "echo a > a\"\"$space\nrm a");
// MINISHELL_TEST(regular_24, "> x\nls");
// MINISHELL_TEST(regular_23, "echo a > \"\"$space\"b\"\nrm b");
// MINISHELL_TEST(regular_11, "echo a > \"c\"$foo\"d\"\nrm cd");
// MINISHELL_TEST(regular_8, "echo a > $whitespace_left\"foo\"\nrm whitespacefoo");
// MINISHELL_TEST(regular_4, "echo a > \"foo \"\"bar\"\nrm \"foo bar\"");
// MINISHELL_TEST(regular_7, "echo a > $whitespace_right $no_whitespace\nrm whitespace");
// MINISHELL_TEST(regular_19, "echo a > \"$whitespace_right\" $no_whitespace\nrm \"whitespace \"");
// MINISHELL_TEST(regular_16, "echo a > $whitespace_left$space\nrm whitespace");
// MINISHELL_TEST(regular_5, "echo a > \"foo \"$no_whitespace\nrm \"foo no_whitespace\"");
// MINISHELL_TEST(regular_14, "echo a > $space$whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_3, "echo a > $no_whitespace $whitespace_left\nrm no_whitespace");
// MINISHELL_TEST(regular_17, "echo a > \"foo\"\'$whitespace_left\'\nrm \'foo$whitespace_left\'");
// MINISHELL_TEST(regular_20, "echo a > \"$whitespace_left\"\"foo\"\nrm \" whitespacefoo\"");
//
//
// /*******************************************************************************/
// /*                       no_such_file_or_directory                            */
// /*******************************************************************************/
//
// MINISHELL_TEST(no_file_or_dir_2, "echo a > \"$foo\"");
// MINISHELL_TEST(no_file_or_dir_1, "echo a > \"\"");
// MINISHELL_TEST(no_file_or_dir_4, "echo a > $empty\"\"");
// MINISHELL_TEST(no_file_or_dir_5, "echo a > \'\' \'\' \'hello\'");
// MINISHELL_TEST(no_file_or_dir_3, "echo a > \"\"$empty");
//
//
// /*******************************************************************************/
// /*                                  chmod                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(chmod_read_inaccessible_file, "echo a > foo\nchmod 0 foo\n< foo cat");
// MINISHELL_TEST(chmod_append_to_inaccessible_file, "echo a > foo\nchmod 0 foo\necho b >> foo");
// MINISHELL_TEST(chmod_overwrite_inaccessible_file, "echo a > foo\nchmod 0 foo\necho b > foo");
//
//
// /*******************************************************************************/
// /*                              syntax_error                                  */
// /*******************************************************************************/
//
// MINISHELL_TEST(syntax_2, "echo a > 2 > x");
// MINISHELL_TEST(syntax_1, "echo a >");
//
//
// /*******************************************************************************/
// /*                          ambiguous_redirect                               */
// /*******************************************************************************/
//
// MINISHELL_TEST(redirect_ambiguous_15, "echo a > $space");
// MINISHELL_TEST(redirect_ambiguous_9, "echo a > \"foo\"\" bar\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_13, "echo a > \"foo\"$whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_6, "echo a > $whitespace_right$no_whitespace");
// MINISHELL_TEST(redirect_ambiguous_21, "echo a > $empty");
// MINISHELL_TEST(redirect_ambiguous_12, "echo a > \" \"\"\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_27, "> $empty");
// MINISHELL_TEST(redirect_ambiguous_28, "< foo");
// MINISHELL_TEST(redirect_ambiguous_10, "echo a > $whitespace_left$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_25, "touch exists\n< $exists < x echo\nrm exists");
// MINISHELL_TEST(redirect_ambiguous_2, "echo a > $whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_18, "< $empty x");
// MINISHELL_TEST(redirect_ambiguous_34, "echo a > foo\'\'$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_32, "echo a > $whitespace_right\'\'");
// MINISHELL_TEST(redirect_ambiguous_31, "echo a > $whitespace_right$space");
// MINISHELL_TEST(redirect_ambiguous_1, "echo a > \"foo\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_29, "> foo");
// MINISHELL_TEST(redirect_ambiguous_22, "echo a > \"\"$space");
// MINISHELL_TEST(redirect_ambiguous_24, "touch exists\n< x < $exists echo\nrm exists");
// MINISHELL_TEST(redirect_ambiguous_23, "echo a > $space\"\"");
// MINISHELL_TEST(redirect_ambiguous_26, "< $empty");
// MINISHELL_TEST(redirect_ambiguous_33, "echo a > $whitespace_right\'\'foo");
// MINISHELL_TEST(redirect_ambiguous_30, "echo a > $whitespace_right\" \"");
// MINISHELL_TEST(redirect_ambiguous_11, "echo a > \" \"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_8, "echo a > \"foo\"\"bar\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_4, "echo a > $no_whitespace$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_7, "echo a > $foo\nrm $foo");
// MINISHELL_TEST(redirect_ambiguous_19, "x < $empty");
// MINISHELL_TEST(redirect_ambiguous_16, "< $whitespace_center cat");
// MINISHELL_TEST(redirect_ambiguous_5, "echo a > $whitespace_right\"foo\"");
// MINISHELL_TEST(redirect_ambiguous_14, "echo a > \"foo\"$whitespace_right\"bar\"");
// MINISHELL_TEST(redirect_ambiguous_35, "echo a > $space\'\'hello");
// MINISHELL_TEST(redirect_ambiguous_3, "echo a > $whitespace_right\"foo\"");
// MINISHELL_TEST(redirect_ambiguous_17, "< $whitespace_center cat > $whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_20, "< $space x");
//
//
// /*******************************************************************************/
// /*                                  heredocs                                    */
// /*******************************************************************************/
//
// MINISHELL_TEST(heredocs_two_heredocs_no_command, "<< a << b\nfoo\na\nbar\nb");
// MINISHELL_TEST(heredocs_two_heredocs, "<< a << b cat\nfoo\na\nbar\nb");
// MINISHELL_TEST(heredocs_unexpanded_double_quoted_word, "<< \"$USER\" cat\n$?\n$USER");
// MINISHELL_TEST(heredocs_heredoc_and_ambiguous, "<<eof <$whitespace_center");
// MINISHELL_TEST(heredocs_multiple_token_types_in_delimiter, "<< foo\'bar\'\"baz\"$whitespace_center cat\na\nfoobarbaz$whitespace_center\nb");
// MINISHELL_TEST(heredocs_single_quoted_word, "<< \'EOF\' cat\n$?\nEOF\n\n<< \'EOF\' cat\n\"$?\"\nEOF\n\n<< \'EOF\' cat\n\'$?\'\nEOF\n\nrm .\n<< \'EOF\' cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_unquoted_word, "<< EOF cat\n$?\nEOF\n\n<< EOF cat\n\"$?\"\nEOF\n\n<< EOF cat\n\'$?\'\nEOF\n\nrm .\n<< EOF cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_word_directly_after_heredoc, "<<EOF cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_double_quoted_delimiter, "<< \"EOF\" cat\n$?\n\"EOF\"");
// MINISHELL_TEST(heredocs_single_quoted_delimiter, "<< \"EOF\" cat\n$?\n\'EOF\'");
// MINISHELL_TEST(heredocs_double_quoted_word, "<< \"EOF\" cat\n$?\nEOF\n\n<< \"EOF\" cat\n\"$?\"\nEOF\n\n<< \"EOF\" cat\n\'$?\'\nEOF\n\nrm .\n<< \"EOF\" cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_heredoc_without_delimiter, "<<");
// MINISHELL_TEST(heredocs_no_such_file_or_directory_command, "<< eof cat < bar\na\neof");
// MINISHELL_TEST(heredocs_halfway_no_such_file_or_directory, "echo hello > foo\nrm bar\n<< eof1 cat < bar << eof2 < foo\na\neof1\nb\neof2");
// MINISHELL_TEST(heredocs_unexpanded_single_quoted_word, "<< \'$USER\' cat\n$?\n$USER");
// MINISHELL_TEST(heredocs_no_word_expansion, "export a=\"a b\"\n\n<< $a cat\n$USER\n$a");
// MINISHELL_TEST(heredocs_no_such_file_or_directory_builtin, "<< eof echo < bar\na\neof");
//
//
// /*******************************************************************************/
// /*                               files                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(files_append_create, "echo a >> foo\necho b >> foo\ncat foo");
// MINISHELL_TEST(files_append, "echo a > foo\necho b >> foo\ncat foo");
// MINISHELL_TEST(files_recreate, "echo a > foo\necho b > foo\ncat foo");
// MINISHELL_TEST(files_create, "echo a > foo\ncat foo");
//
//
// /*******************************************************************************/
// /*                                  rmdir                                      */
// /*******************************************************************************/
//
// MINISHELL_TEST(rmdir_invalid_argument, "rmdir .");
//
//
// /*******************************************************************************/
// /*                              syntax_errors                                  */
// /*******************************************************************************/
//

/*******************************************************************************/
/*                                  unset                                      */
/*******************************************************************************/

// PASSING
MINISHELL_TEST(unset_cd_home, "unset HOME\ncd\npwd\n");
// FAILING
MINISHELL_TEST(unset_multiple, "unset USER HOME\nenv | sort\n");

/*******************************************************************************/
/*                                  cd                                       */
/*******************************************************************************/

// PASSING
MINISHELL_TEST(cd_twice, "cd / | cd /\npwd\n");
// FAILING
MINISHELL_TEST(cd_no_args, "cd\npwd\n");
MINISHELL_TEST(cd_dir_up, "pwd\ncd ..\npwd\n");
MINISHELL_TEST(cd_no_args_pwd, "cd\npwd\n");
MINISHELL_TEST(cd_pipeline_twice, "cd $HOME\ncd / | cd /\npwd\n");
MINISHELL_TEST(cd_no_home, "unset HOME\ncd /\ncd asd\npwd\n");
MINISHELL_TEST(cd_slash, "cd /\npwd\n");
MINISHELL_TEST(cd_pipeline_last, "cd $HOME\npwd | cd /\npwd\n");
MINISHELL_TEST(cd_first_pipeline, "cd $HOME\ncd / | pwd\npwd\n");
MINISHELL_TEST(cd_nonexistent, "cd /\ncd nonexistent\npwd\n");

/*******************************************************************************/
/*                                  mkdir                                      */
/*******************************************************************************/

MINISHELL_TEST(mkdir_rmdir, "mkdir build/test\nrmdir build/test\n");
MINISHELL_TEST(mkdir_file_exists, "rmdir build/test\nmkdir build/test\nmkdir build/test\nrmdir build/test\n");

/*******************************************************************************/
/*                              Syntax_erros                                  */
/*******************************************************************************/

MINISHELL_TEST(syntax_triple_forward_redirect, "ls <<<\n");
MINISHELL_TEST(syntax_unmatched_double_quote, "\"\n");
MINISHELL_TEST(syntax_redirection_kiss, "ls><abc\n");
MINISHELL_TEST(syntax_echo, "echo \'a\n");
MINISHELL_TEST(syntax_unmatched_word_double_quote, "<< \"EOF cat\n$?\nEOF\n");
MINISHELL_TEST(syntax_export_equals_redirection, "export a=>\n");
MINISHELL_TEST(syntax_no_such_file_or_directory_syntax_error, "/a |\n");
MINISHELL_TEST(syntax_redirection, ">\n");
MINISHELL_TEST(syntax_unmatched_word_single_quote, "<< \'EOF cat\n$?\nEOF\n");
MINISHELL_TEST(syntax_unmatched_single_quote, "\'\n");

MINISHELL_TEST(syntax_pipe_only, "|\n");
MINISHELL_TEST(syntax_pipe_only, "||\n");
MINISHELL_TEST(syntax_double_pipe, "pwd ||\n");
MINISHELL_TEST(syntax_export_equals_pipe, "export a=|\n");
MINISHELL_TEST(syntax_redirection_no_file_and_pipe, "echo a > |\n");

MINISHELL_TEST(syntax_pipe_before, "| ls\n");
MINISHELL_TEST(syntax_pipe_before_double, "| | ls\n");
MINISHELL_TEST(syntax_pipe_before_input, "< | ls\n");
MINISHELL_TEST(syntax_pipe_before_ouput, "> | ls\n");
MINISHELL_TEST(syntax_pipe_before_heredoc, "<< | ls\n");
MINISHELL_TEST(syntax_pipe_before_append, ">> | ls\n");
MINISHELL_TEST(syntax_pipe_before_single_quotes, "\'\' | ls\n");
MINISHELL_TEST(syntax_pipe_before_double_quotes, "\"\" | ls\n");

MINISHELL_TEST(syntax_pipe_after, "ls |\n");
MINISHELL_TEST(syntax_pipe_after_double, "ls | |\n");
MINISHELL_TEST(syntax_pipe_after_input, "ls | <\n");
MINISHELL_TEST(syntax_pipe_after_output, "ls | >\n");
MINISHELL_TEST(syntax_pipe_after_heredoc, "ls | <<\n");
MINISHELL_TEST(syntax_pipe_after_append, "ls | >>\n");
MINISHELL_TEST(syntax_pipe_after_single_quotes, "ls | \'\'\n");
MINISHELL_TEST(syntax_pipe_after_double_quotes, "ls | \"\"\n");
