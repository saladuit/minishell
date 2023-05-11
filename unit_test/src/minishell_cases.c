/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   minishell_cases.c                               |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:34:16 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:34:16 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

#define MINISHELL_TEST(test_case, command_line) \
    Test(minishell, test_case) { \
        assert_minishell(command_line, #test_case); \
    }

extern char	**environ;

void	redirect_stdfds(void)
{
	cr_redirect_stdout();
	cr_redirect_stdin();
	cr_redirect_stderr();
}

int32_t		minishell_loop(t_minishell *sheldon);

TestSuite(minishell, .init = redirect_stdfds);

static int	read_from_file(void *cookie, void *buffer, size_t *size)
{
	FILE	*file;
	size_t	read_size;

	file = (FILE *)cookie;
	read_size = fread(buffer, 1, *size, file);
	cr_assert(read_size <= *size, "fread failed");
	*size = read_size;
	return (0);
}

static char *create_txt_file_path(const char *case_name)
{
    char *txt_file_path;

    txt_file_path = calloc(strlen(case_name) + 27, sizeof(char));
    cr_assert(txt_file_path != NULL, "calloc failed");
    snprintf(txt_file_path, strlen(case_name) + 27, "build/%s.txt", case_name);
    cr_log_info("txt_file_path: %s", txt_file_path);
    return (txt_file_path);
}

static char *create_system_call(const char *command_line, const char *txt_file_path)
{
    char *system_call;

    system_call = calloc(strlen(txt_file_path) + strlen(command_line) + 26, sizeof(char));
    cr_assert(system_call != NULL, "calloc failed");
    snprintf(system_call, strlen(txt_file_path) + strlen(command_line) + 26, "bash -c \'%s\necho $?\' >| %s", command_line, txt_file_path);
    cr_log_info("system_call: %s", system_call);
    return (system_call);
}

static char *create_minishell_command(const char *command_line)
{
    char *minishell_command;

    minishell_command = calloc(strlen(command_line) + 1, sizeof(char));
    cr_assert(minishell_command != NULL, "calloc failed");
    snprintf(minishell_command, strlen(command_line) + 1,"%s", command_line);
    cr_log_info("minishell_command: %s", minishell_command);
    return (minishell_command);
}

static void setup_streams(struct cr_stream *actual, struct cr_stream *expected, const char *txt_file_path)
{
    actual->cookie = cr_get_redirected_stdout();
    cr_assert(actual->cookie != NULL, "cr_get_redirected_stdout failed");
    actual->read = read_from_file;

    expected->cookie = fopen(txt_file_path, "r");
    cr_assert(expected->cookie != NULL, "fopen failed");
    expected->read = read_from_file;

    cr_stream_init(expected);
    cr_stream_init(actual);
}

void assert_minishell(char *command_line, char *case_name)
{
    struct cr_stream actual;
    struct cr_stream expected;
    char *txt_file_path;
    char *system_call;
    char *minishell_command;
    FILE *f_stdin;
    int32_t ret;
    const unsigned char hex = 0x0a;

    f_stdin = cr_get_redirected_stdin();
    cr_assert(f_stdin != NULL, "cr_get_redirected_stdin failed");

    txt_file_path = create_txt_file_path(case_name);
    system_call = create_system_call(command_line, txt_file_path);
    minishell_command = create_minishell_command(command_line);
    cr_assert(fputs(minishell_command, f_stdin) >= 0, "fputs failed");
    cr_assert(fclose(f_stdin) == 0, "fclose failed");

    system(system_call);

    setup_streams(&actual, &expected, txt_file_path);

    ret = minishell(environ);
    fprintf(stdout, "%d%c", ret, hex);
    fflush(stdout);
    fflush(stdin);
    fflush(stderr);

    cr_assert(eq(stream, expected, actual));
    fclose(expected.cookie);

    free(txt_file_path);
    free(system_call);
    free(minishell_command);
}

/*******************************************************************************/
/*                              Bacis_tests                                    */
/*******************************************************************************/
MINISHELL_TEST(empty, "");
MINISHELL_TEST(invalid_command, "invalid_command");
MINISHELL_TEST(absolute_invalid_command, "/invalid_command");
MINISHELL_TEST(relative_invalid_command, "relavtive/invalid_command");
MINISHELL_TEST(spaces, "     ");
MINISHELL_TEST(tab, "\t");


/*******************************************************************************/
/*                              Miscellaneous                                  */
/*******************************************************************************/

MINISHELL_TEST(execution_invalid_path, "/made/up/path");
MINISHELL_TEST(execution_basic,"ls .\nl\"s\" .\nl\'s\' .\nexport s=\" s\"\nl$s .\nexport s=\"s\"\nl$s .\nlsX .");
MINISHELL_TEST(execution_leading_whitespace, " a");
// MINISHELL_TEST(execution_space_in_string, "\' \'");
MINISHELL_TEST(execution_ls, "ls");
MINISHELL_TEST(execution_space, "");
MINISHELL_TEST(execution_trailing_whitespace, "a ");
// MINISHELL_TEST(execution_whitespace_center, "$whitespace_center");
MINISHELL_TEST(execution_command_not_found, "asd");
MINISHELL_TEST(execution_command_not_found_and_no_such_file_or_directory, "asd\n/asd\ncat foo");

/*******************************************************************************/
/*                               exit_status                                   */
/*******************************************************************************/

MINISHELL_TEST(exit_status_basic, "echo hello\necho $?");
MINISHELL_TEST(exit_status_trailing, "echo $?a\necho $??\necho $?$?\necho $?$?a");
// MINISHELL_TEST(exit_status_error, "rm .\necho $?");

/*******************************************************************************/
/*                                  cat                                       */
/*******************************************************************************/

MINISHELL_TEST(cat_me_relative, "cat /Makefile");
MINISHELL_TEST(cat_me, "cat sample-txt/cat-me.txt | grep cat | wc -w");

/*******************************************************************************/
/*                                  pipes                                      */
/*******************************************************************************/

MINISHELL_TEST(pipes_ls_grep_t, "cat < Makefile | grep t");
// MINISHELL_TEST(pipes_redir_and_pipe, "cat > build/pipes_redir_and_pipe_cat.txt\nsort < pipes_redir_and_pipe_cat.txt | grep t");
MINISHELL_TEST(execution_pipeline_command_not_found, "echo | command_not_found");

/*******************************************************************************/
/*                                  Expansion                                 */
/*******************************************************************************/

// MINISHELL_TEST(execution_empty_single_quotes, "\'\'");
MINISHELL_TEST(execution_empty_double_quotes, "\"\"");
MINISHELL_TEST(expansion_1, "echo $?");
MINISHELL_TEST(expansion_2, "echo $?$?");
MINISHELL_TEST(expansion_3, "echo foo$?");
MINISHELL_TEST(expansion_4, "echo $?foo");
MINISHELL_TEST(expansion_5, "echo $");
// MINISHELL_TEST(expansion_6, "echo $_x");
MINISHELL_TEST(expansion_7, "echo $ax");
MINISHELL_TEST(expansion_8, "echo $1x");
MINISHELL_TEST(expansion_9, "echo $11");
// MINISHELL_TEST(expansion_10, "echo $@1");
MINISHELL_TEST(expansion_11, "echo $ 1");
MINISHELL_TEST(expansion_12, "echo $x_");
// MINISHELL_TEST(expansion_13, "echo $xa");
// MINISHELL_TEST(expansion_14, "echo $x1");
// MINISHELL_TEST(expansion_15, "echo 1$USER-");
// MINISHELL_TEST(expansion_16, "echo 1$USER$USER-");
// MINISHELL_TEST(expansion_17, "echo a b");
// MINISHELL_TEST(expansion_18, "echo @ b");
// MINISHELL_TEST(execution_ls_expansion_2,
// "ls $whitespace_center$whitespace_center");
// MINISHELL_TEST(execution_env_expansion_splitting_space_right,
// "export a=\"b \"\necho foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_space,
// "export a=\" \"\necho foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_spaces_everywhere,
// "export a=\" b c \"\necho foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_empty,
// "export a=\"\"\nls foo $a bar");
// MINISHELL_TEST(execution_env_expansion_splitting_left_space_separator,
// "export a=\" b\"\necho foo$a\"bar\"");
// MINISHELL_TEST(execution_env_expansion_splitting_space_left,
// "export a=\" b\"\necho foo $a bar");
// MINISHELL_TEST(execution_pipeline_expansion,
		// "export a=\"| ls\"\n$a");
// MINISHELL_TEST(execution_env_expansion_splitting_space_separator,
// "export a=\" \"\necho foo$a\"bar\"");
// MINISHELL_TEST(execution_ls_expansion, "ls $whitespace_center");

/*******************************************************************************/
/*                              redirections                                  */
/*******************************************************************************/

// MINISHELL_TEST(redirect_redirection_in,
		// "ls > abc\n< abc sort\nrm abc");
// MINISHELL_TEST(redirect_last_input_is_read,
// "echo a > a\necho b > b\necho c > c\necho d > d\n\n< a < b cat < c < d");
// MINISHELL_TEST(redirect_cat_redirection_created_file,
// "ls > abc\ncat abc\nrm abc");
// MINISHELL_TEST(redirect_create_files,
// "pwd > a > b\ncat a\ncat b\nls\nrm a\nrm b");
// MINISHELL_TEST(redirect_last_output_is_written_to,
// "> a > b echo x > c > d\necho y\ncat a\necho y\ncat b\necho y\ncat c\necho y\ncat d\necho y");
// MINISHELL_TEST(create_files, "pwd >> a >> b >> b\ncat a\ncat b\nls");
// MINISHELL_TEST(regular_15,
		// "echo a > \'\'$whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_9,
// "echo a > \"foo\"$whitespace_right\nrm foowhitespace");
// MINISHELL_TEST(regular_13, "echo a > \'$foo\'\nrm $foo");
// MINISHELL_TEST(regular_6,
// "echo a > $whitespace_right \"foo\"\nrm whitespace");
// MINISHELL_TEST(regular_21, "< x echo");
// MINISHELL_TEST(regular_12, "echo a > \"c\"$empty\"d\"\nrm cd");
// MINISHELL_TEST(regular_10, "echo a > \"c\"$food\nrm c");
// MINISHELL_TEST(regular_2,
		// "echo a > \"foo\" $whitespace_left\nrm foo");
// MINISHELL_TEST(regular_18,
// "echo a > \"foo\"\"$whitespace_left\"\nrm \"foo whitespace\"");
// MINISHELL_TEST(regular_1,
		// "echo a > $whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_22, "echo a > a\"\"$space\nrm a");
// MINISHELL_TEST(regular_24, "> x\nls");
// MINISHELL_TEST(regular_23, "echo a > \"\"$space\"b\"\nrm b");
// MINISHELL_TEST(regular_11, "echo a > \"c\"$foo\"d\"\nrm cd");
// MINISHELL_TEST(regular_8,
// "echo a > $whitespace_left\"foo\"\nrm whitespacefoo");
// MINISHELL_TEST(regular_4,
		// "echo a > \"foo \"\"bar\"\nrm \"foo bar\"");
// MINISHELL_TEST(regular_7,
// "echo a > $whitespace_right $no_whitespace\nrm whitespace");
// MINISHELL_TEST(regular_19,
// "echo a > \"$whitespace_right\" $no_whitespace\nrm \"whitespace \"");
// MINISHELL_TEST(regular_16,
		// "echo a > $whitespace_left$space\nrm whitespace");
// MINISHELL_TEST(regular_5,
// "echo a > \"foo \"$no_whitespace\nrm \"foo no_whitespace\"");
// MINISHELL_TEST(regular_14,
		// "echo a > $space$whitespace_left\nrm whitespace");
// MINISHELL_TEST(regular_3,
// "echo a > $no_whitespace $whitespace_left\nrm no_whitespace");
// MINISHELL_TEST(regular_17,
// "echo a > \"foo\"\'$whitespace_left\'\nrm \'foo$whitespace_left\'");
// MINISHELL_TEST(regular_20,
// "echo a > \"$whitespace_left\"\"foo\"\nrm \" whitespacefoo\"");
// MINISHELL_TEST(no_file_or_dir_2, "echo a > \"$foo\"");
// MINISHELL_TEST(no_file_or_dir_1, "echo a > \"\"");
// MINISHELL_TEST(no_file_or_dir_4, "echo a > $empty\"\"");
// MINISHELL_TEST(no_file_or_dir_5, "echo a > \'\' \'\' \'hello\'");
// MINISHELL_TEST(no_file_or_dir_3, "echo a > \"\"$empty");

/*******************************************************************************/
/*                          ambiguous_redirect                               */
/*******************************************************************************/

// MINISHELL_TEST(redirect_ambiguous_15, "echo a > $space");
// MINISHELL_TEST(redirect_ambiguous_9,
// "echo a > \"foo\"\" bar\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_13,
		// "echo a > \"foo\"$whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_6,
// "echo a > $whitespace_right$no_whitespace");
// MINISHELL_TEST(redirect_ambiguous_21, "echo a > $empty");
// MINISHELL_TEST(redirect_ambiguous_12,
		// "echo a > \" \"\"\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_27, "> $empty");
// MINISHELL_TEST(redirect_ambiguous_28, "< foo");
// MINISHELL_TEST(redirect_ambiguous_10,
// "echo a > $whitespace_left$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_25,
// "touch exists\n< $exists < x echo\nrm exists");
// MINISHELL_TEST(redirect_ambiguous_2, "echo a > $whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_18, "< $empty x");
// MINISHELL_TEST(redirect_ambiguous_34,
		// "echo a > foo\'\'$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_32,
		// "echo a > $whitespace_right\'\'");
// MINISHELL_TEST(redirect_ambiguous_31,
		// "echo a > $whitespace_right$space");
// MINISHELL_TEST(redirect_ambiguous_1,
		// "echo a > \"foo\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_29, "> foo");
// MINISHELL_TEST(redirect_ambiguous_22, "echo a > \"\"$space");
// MINISHELL_TEST(redirect_ambiguous_24,
// "touch exists\n< x < $exists echo\nrm exists");
// MINISHELL_TEST(redirect_ambiguous_23, "echo a > $space\"\"");
// MINISHELL_TEST(redirect_ambiguous_26, "< $empty");
// MINISHELL_TEST(redirect_ambiguous_33,
		// "echo a > $whitespace_right\'\'foo");
// MINISHELL_TEST(redirect_ambiguous_30,
		// "echo a > $whitespace_right\" \"");
// MINISHELL_TEST(redirect_ambiguous_11,
		// "echo a > \" \"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_8,
// "echo a > \"foo\"\"bar\"$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_4,
// "echo a > $no_whitespace$whitespace_left");
// MINISHELL_TEST(redirect_ambiguous_7, "echo a > $foo\nrm $foo");
// MINISHELL_TEST(redirect_ambiguous_19, "x < $empty");
// MINISHELL_TEST(redirect_ambiguous_16, "< $whitespace_center cat");
// MINISHELL_TEST(redirect_ambiguous_5,
		// "echo a > $whitespace_right\"foo\"");
// MINISHELL_TEST(redirect_ambiguous_14,
// "echo a > \"foo\"$whitespace_right\"bar\"");
// MINISHELL_TEST(redirect_ambiguous_35, "echo a > $space\'\'hello");
// MINISHELL_TEST(redirect_ambiguous_3,
		// "echo a > $whitespace_right\"foo\"");
// MINISHELL_TEST(redirect_ambiguous_17,
// "< $whitespace_center cat > $whitespace_center");
// MINISHELL_TEST(redirect_ambiguous_20, "< $space x");

/*******************************************************************************/
/*                                  heredocs                                    */
/*******************************************************************************/

// MINISHELL_TEST(heredocs_two_heredocs_no_command,
// "<< a << b\nfoo\na\nbar\nb");
// MINISHELL_TEST(heredocs_two_heredocs,
		// "<< a << b cat\nfoo\na\nbar\nb");
// MINISHELL_TEST(heredocs_unexpanded_double_quoted_word,
// "<< \"$USER\" cat\n$?\n$USER");
// MINISHELL_TEST(heredocs_heredoc_and_ambiguous,
		// "<<eof <$whitespace_center");
// MINISHELL_TEST(heredocs_multiple_token_types_in_delimiter,
// "<< foo\'bar\'\"baz\"$whitespace_center cat\na\nfoobarbaz$whitespace_center\nb");
// MINISHELL_TEST(heredocs_single_quoted_word,
// "<< \'EOF\' cat\n$?\nEOF\n\n<< \'EOF\' cat\n\"$?\"\nEOF\n\n<< \'EOF\' cat\n\'$?\'\nEOF\n\nrm .\n<< \'EOF\' cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_unquoted_word,
// "<< EOF cat\n$?\nEOF\n\n<< EOF cat\n\"$?\"\nEOF\n\n<< EOF cat\n\'$?\'\nEOF\n\nrm .\n<< EOF cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_word_directly_after_heredoc,
		// "<<EOF cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_double_quoted_delimiter,
// "<< \"EOF\" cat\n$?\n\"EOF\"");
// MINISHELL_TEST(heredocs_single_quoted_delimiter,
// "<< \"EOF\" cat\n$?\n\'EOF\'");
// MINISHELL_TEST(heredocs_double_quoted_word,
// "<< \"EOF\" cat\n$?\nEOF\n\n<< \"EOF\" cat\n\"$?\"\nEOF\n\n<< \"EOF\" cat\n\'$?\'\nEOF\n\nrm .\n<< \"EOF\" cat\n$?\nEOF");
// MINISHELL_TEST(heredocs_heredoc_without_delimiter, "<<");
// MINISHELL_TEST(heredocs_no_such_file_or_directory_command,
// "<< eof cat < bar\na\neof");
// MINISHELL_TEST(heredocs_halfway_no_such_file_or_directory,
// "echo hello > foo\nrm bar\n<< eof1 cat < bar << eof2 < foo\na\neof1\nb\neof2");
// MINISHELL_TEST(heredocs_unexpanded_single_quoted_word,
// "<< \'$USER\' cat\n$?\n$USER");
// MINISHELL_TEST(heredocs_no_word_expansion,
// "export a=\"a b\"\n\n<< $a cat\n$USER\n$a");
// MINISHELL_TEST(heredocs_no_such_file_or_directory_builtin,
// "<< eof echo < bar\na\neof");

/*******************************************************************************/
/*                               files                                         */
/*******************************************************************************/

// MINISHELL_TEST(files_create,
// "echo a > build/echo_create.txt\ncat build/echo_create.txt");
// MINISHELL_TEST(files_fail,
// "echo a > build/echo_fail.txt\necho b > build/echo_fail.txt\nrm build/echo_fail.txt");
// MINISHELL_TEST(files_append,
// "echo a > build/echo_append.txt\necho b >> build/echo_append.txt\ncat build/echo_append.txt\nrm build/echo_append.txt");
// MINISHELL_TEST(files_append_create,
// "echo a >> build/echo_append_create.txt\necho b >> build/echo_append_create.txt\ncat build/echo_append_create.txt\nrm build/echo_append_create.txt");

/*******************************************************************************/
/*                              Syntax_erros                                   */
/*******************************************************************************/

// MINISHELL_TEST(syntax_2, "echo a > 2 > x");
	//FIXME generates unwanted file
// MINISHELL_TEST(syntax_1, "echo a >");
// MINISHELL_TEST(syntax_triple_forward_redirect, "ls <<<");
// MINISHELL_TEST(syntax_unmatched_double_quote, "\"");
// MINISHELL_TEST(syntax_redirection_kiss, "ls><abc");
// MINISHELL_TEST(syntax_echo, "echo \'a");
// MINISHELL_TEST(syntax_unmatched_word_double_quote,
		// "<< \"EOF cat\n$?\nEOF");
// MINISHELL_TEST(syntax_export_equals_redirection, "export a=>");
// MINISHELL_TEST(syntax_no_such_file_or_directory_syntax_error,
		// "/a |");
// MINISHELL_TEST(syntax_redirection, ">");
// MINISHELL_TEST(syntax_unmatched_word_single_quote,
		// "<< \'EOF cat\n$?\nEOF");
// MINISHELL_TEST(syntax_unmatched_single_quote, "\'");

// MINISHELL_TEST(syntax_pipe_only, "|");
// MINISHELL_TEST(syntax_pipe_double, "||");
// MINISHELL_TEST(syntax_double_pipe, "pwd ||");
// MINISHELL_TEST(syntax_export_equals_pipe, "export a=|");
// MINISHELL_TEST(syntax_redirection_no_file_and_pipe, "echo a > |\n");

// MINISHELL_TEST(syntax_pipe_before, "| ls");
// MINISHELL_TEST(syntax_pipe_before_double, "| | ls");
// MINISHELL_TEST(syntax_pipe_before_input, "< | ls");
// MINISHELL_TEST(syntax_pipe_before_heredoc, "<< | ls");
// MINISHELL_TEST(syntax_pipe_before_ouput, "> | ls\n rm \|\n");
//FIXME same this | symbol cannot be removed
// MINISHELL_TEST(syntax_pipe_before_append, ">> | ls\n"); //FIXME same
// MINISHELL_TEST(syntax_pipe_before_single_quotes, "\'\' | ls");
// MINISHELL_TEST(syntax_pipe_before_double_quotes, "\"\" | ls");

// MINISHELL_TEST(syntax_pipe_after, "ls |");
// MINISHELL_TEST(syntax_pipe_after_double, "ls | |");
// MINISHELL_TEST(syntax_pipe_after_input, "ls | <");
// MINISHELL_TEST(syntax_pipe_after_heredoc, "ls | <<"); //FIXME same
// MINISHELL_TEST(syntax_pipe_after_output, "ls | >");//FIXME same
// MINISHELL_TEST(syntax_pipe_after_append, "ls | >>");//FIXME same
// MINISHELL_TEST(syntax_pipe_after_single_quotes, "ls | \'\'");
// MINISHELL_TEST(syntax_pipe_after_double_quotes, "ls | \"\"");

/*******************************************************************************/
/*                                   Builtins                                  */
/*******************************************************************************/

/*******************************************************************************/
/*                                   echo                                      */
/*******************************************************************************/

MINISHELL_TEST(echo, "echo");
MINISHELL_TEST(echo_leading_whitespace, " echo");
MINISHELL_TEST(echo_trailing_whitespace, "echo ");
MINISHELL_TEST(echo_one_argument, "echo a");
MINISHELL_TEST(echo_two_arguments, "echo a b");
MINISHELL_TEST(echo_pipe_echo, "echo | echo");
MINISHELL_TEST(echo_pipe_echo_pipe_echo, "echo | echo | echo");
MINISHELL_TEST(echo_pipe_echo_status, "echo | echo $?");
MINISHELL_TEST(echo_hello, "echo hello");
MINISHELL_TEST(echo_n_option_several, "echo -n -n a -n -n");
MINISHELL_TEST(echo_n_option_nn, "echo -nn a -nn");
MINISHELL_TEST(echo_n_option_nan, "echo -nan a -nan");
// MINISHELL_TEST(echo_n_option_na, "echo -na a -na");
// MINISHELL_TEST(echo_n_option_ana, "echo -ana a -ana");
// MINISHELL_TEST(echo_n_option_an, "echo -an a -an");
// MINISHELL_TEST(echo_n_option_first, "echo -n a\necho -n a b");
// MINISHELL_TEST(echo_n_option_last, "echo a -n\necho a b -n");
// MINISHELL_TEST(echo_expansion, "echo $whitespace_center");

/*******************************************************************************/
/*                                  cd                                         */
/*******************************************************************************/

// PASSING
MINISHELL_TEST(cd_twice, "cd / | cd /\npwd");
MINISHELL_TEST(cd_no_args, "cd\npwd");
MINISHELL_TEST(cd_dir_up, "pwd\ncd ..\npwd");
MINISHELL_TEST(cd_pipeline_twice, "cd $HOME\ncd / | cd /\npwd");
MINISHELL_TEST(cd_no_home, "unset HOME\ncd /\ncd asd\npwd");
MINISHELL_TEST(cd_absolute, "cd /\npwd");
MINISHELL_TEST(cd_pipeline_last, "cd $HOME\npwd | cd /\npwd");
MINISHELL_TEST(cd_first_pipeline, "cd $HOME\ncd / | pwd\npwd");
// MINISHELL_TEST(cd_nonexistent, "cd /\ncd nonexistent\npwd");

/*******************************************************************************/
/*                                  pwd                                       */
/*******************************************************************************/

MINISHELL_TEST(pwd, "pwd");
MINISHELL_TEST(pwd_arg, "pwd arg");
// MINISHELL_TEST(pwd_removed_dir, "mkdir test\ncd test\nrmdir/tmp/test\npwd");

/*******************************************************************************/
/*                                  export                                     */
/*******************************************************************************/

//FIXME All of these test cases should be echo'd they probably don't work
// NUL
// MINISHELL_TEST(export_NULL, "export 0=NUL");
// MINISHELL_TEST(export_NULL_1, "export \0=NULL");
// MINISHELL_TEST(export_NULL_2, "export \\\0=NULL");
// MINISHELL_TEST(export_NULL_3, "export NUL\\\0=NULL");
// MINISHELL_TEST(export_NULL_4, "export \\\0NUL=NULL");
// MINISHELL_TEST(export_NULL_single_quote_1, "export '0'=NUL");
// MINISHELL_TEST(export_NULL_single_quote_2, "export '\0'=NULL");
// MINISHELL_TEST(export_NULL_single_quote_3, "export '\\\0'=NULL");
// MINISHELL_TEST(export_NULL_single_quote_4, "export 'NUL\\\0'=NULL");
// MINISHELL_TEST(export_NULL_single_quote_5, "export '\\\0NUL'=NULL");
// MINISHELL_TEST(export_NULL_double_qoute_1, "export \"0\"=NUL");
// MINISHELL_TEST(export_NULL_double_qoute_2, "export \"\0\"=NULL");
// MINISHELL_TEST(export_NULL_double_qoute_3, "export \"\\\0\"=NULL");
// MINISHELL_TEST(export_NULL_double_qoute_4,
		// "export \"NUL\\\0\"=NULL");
// MINISHELL_TEST(export_NULL_double_qoute_5,
		// "export \"\\\0NUL\"=NULL");

//Basic
// MINISHELL_TEST(export, "export");
// MINISHELL_TEST(export_single_character, "export A=single\necho $A");
// MINISHELL_TEST(export_envvar, "export BASIC=basic\necho $BASIC");
// MINISHELL_TEST(export_envvar_single_quoted,
// "export BASIC=\'basic\'\necho $BASIC");
// MINISHELL_TEST(export_envvar_double_quoted,
// "export BASIC=\"basic\"\necho $BASIC");
// MINISHELL_TEST(export_number_as_second_character,
		// "export _ALL_1=all_1");

//Multiple
// MINISHELL_TEST(export_multiple,
// "export MULTI=one\necho $MULTI\nMULTI=two\necho $MULTI");
// MINISHELL_TEST(export_multiple_different,
// "export MULTI=one\necho $MULTI\nMULTI=two\necho $MULTI");
// MINISHELL_TEST(export_multiple_same_value,
		// "export MULTI=same MULTI=same\n");
// MINISHELL_TEST(export_multiple_equals,
		// "export FOO=a=b\nexport | grep FOO");
// MINISHELL_TEST(export_export_multiple,
		// "export a=b x=y\nexport | sort");

//No_value
// MINISHELL_TEST(export_no_value, "export NO_VALUE\necho $NO_VALUE");
// MINISHELL_TEST(export_no_value_equals_sign,
// "export NO_VALUE=\necho $NO_VALUE");
// MINISHELL_TEST(export_overwrite,
// "export a=\"x\"\necho $a\nexport a=\"y\"\necho $a");
// MINISHELL_TEST(export_no_value_overwrite_without_value,
// "export NO_VALUE=\nexport NO_VALUE=\necho $NO_VALUE");
// MINISHELL_TEST(export_no_value_overwrite_with_value,
// "export NO_VALUE=\nexport NO_VALUE=\necho $NO_VALUE");
// MINISHELL_TEST(export_overwrite_with_no_equals,
// "export a=\"x\"\necho $a\nexport a\necho $a");

//invalid
// MINISHELL_TEST(export_invalid_char, "export _@=foo");
// MINISHELL_TEST(export_invalid_number_boundary_min, "export 0=zero");
// MINISHELL_TEST(export_invalid_number_boundary_max, "export 9=nine");
// MINISHELL_TEST(export_valid_and_not_valid_identifier,
// "export 1_INVALID=invalid VALID=valid\necho $1_INVALID $VALID");

// MINISHELL_TEST(export_with_value,
		// "export FOO=BAR\nexport | grep FOO");

// MINISHELL_TEST(export_exports_are_unquoted, "export a=\">\"\n$a b");
// MINISHELL_TEST(export_copying,
// "export a=foo\nexport b=$a\necho $b\n\nexport a=bar\necho $a\necho $b");

/*******************************************************************************/
/*                                  unset                                      */
/*******************************************************************************/

// PASSING
// MINISHELL_TEST(unset_cd_home, "unset HOME\ncd\npwd");
// FAILING
// MINISHELL_TEST(unset_multiple, "unset USER HOME\nenv | sort");
// MINISHELL_TEST(execution_no_PATH, "unset PATH\ncat");
// MINISHELL_TEST(execution_pipeline_no_PATH,
// "unset PATH\necho hi > foo | asd\ncat foo");

/*******************************************************************************/
/*                                  env                                       */
/*******************************************************************************/

// MINISHELL_TEST(env_redirection_in_env,
		// "export a=\">\"\necho x $a y");
// MINISHELL_TEST(env_echo_var, "echo $no_whitespace");
// MINISHELL_TEST(env_sorted, "env | sort");
// MINISHELL_TEST(env_no_such_file_or_directory, "$USER");
// MINISHELL_TEST(env_with_value, "export FOO=BAR\nenv | grep FOO");
// MINISHELL_TEST(env_no_equals, "export FOO\nenv | grep FOO");
// MINISHELL_TEST(env_no_value, "export FOO=\nenv | grep FOO");
// MINISHELL_TEST(env_env_in_env, "export a=\'$empty\'\n$a");
// MINISHELL_TEST(env_dollar, "echo $");

/*******************************************************************************/
/*                                  exit                                      */
/*******************************************************************************/

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

/*******************************************************************************/
/*                                    misc                                      */
/*******************************************************************************/

// MINISHELL_TEST(argv_string_concatenation,
// "/\'Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv\' \'foo\'bar\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"bar\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\" \"bar\"\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"\"bar\"\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\' \'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\'\'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \"foo\"\'bar\'\n/Users/sbos/Documents/Programming/Project-Testers/mini-ms-tester/programs/argv \'foo\'\"bar\"");
// MINISHELL_TEST(ls, "ls\nls nonexistent\nls -la /");

/*******************************************************************************/
/*                                  mkdir & rmdir                              */
/*******************************************************************************/

// MINISHELL_TEST(mkdir_rmdir, "mkdir build/test\nrmdir build/test");
// MINISHELL_TEST(mkdir_file_exists,
// "rmdir build/test\nmkdir build/test\nmkdir build/test\nrmdir build/test");
// MINISHELL_TEST(rmdir_invalid_argument, "rmdir .");

/*******************************************************************************/
/*                              nested_minishell                                */
/*******************************************************************************/

// MINISHELL_TEST(ls, "$minishell_path\nls");

/*******************************************************************************/
/*                                  chmod                                      */
/*******************************************************************************/

// MINISHELL_TEST(chmod_read_inaccessible_file,
// "echo a > foo\nchmod 0 foo\n< foo cat");
// MINISHELL_TEST(chmod_append_to_inaccessible_file,
// "echo a > foo\nchmod 0 foo\necho b >> foo");
// MINISHELL_TEST(chmod_overwrite_inaccessible_file,
// "echo a > foo\nchmod 0 foo\necho b > foo");
