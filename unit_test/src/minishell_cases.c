#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <criterion/new/assert.h>
#include <unit_test.h>


extern char **environ;

void redirect_stdfds(void)
{
    cr_redirect_stdout();
    cr_redirect_stdin();
    cr_redirect_stderr();
}

int32_t	minishell_loop(t_minishell *sheldon);

TestSuite(minishell, .init=redirect_stdfds);

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
    sprintf(txt_file_path, "unit_test/test_files/%s.txt", case_name);

    system_call = calloc(strlen(txt_file_path) + strlen(command_line) + 15, sizeof(char));
    sprintf(system_call, "bash -c \'%s\' >| %s", command_line, txt_file_path);

    minishell_command = calloc(strlen(command_line)+ 4, sizeof(char));
    sprintf(minishell_command, "%sEOF", command_line);

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
}

Test(minishell, pwd_basic)
{
    assert_minishell("pwd\n", "pwd_basic");
}
