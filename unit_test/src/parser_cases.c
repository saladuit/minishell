#include <unit_test.h>

//Test(make_command_table, fixed_tests)
//{
//	parser_test("ls", (const char *[]){"ls"}, (0));
//}
Test(make_command, fixed_tests)
{
	get_command_test("ls", (const char *[]){"ls", NULL});
	get_command_test("ls la", (const char *[]){"ls", "la", NULL});
	get_command_test("ls la |", (const char *[]){"ls", "la",  NULL});
	get_command_test("ls la < ", (const char *[]){"ls", "la",  NULL});
}

//Test(make_redirection, fixed_tests)
//{
//	get_redir_test("< test", (const char *[]){"<", "test",  NULL});
//}
