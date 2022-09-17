#include "unit_test.h"

//Test(so_long, fixed_tests)
//{
//	so_long_helper(1, (const char *[]){"1"}, true);
//}

//Test(minishell, fixed_tests)
//{
//	minishell_test(NULL, 0, EXIT_SUCCESS);
//}

Test(lexer, valid_input)
{
	lexer_test("ls", (const char *[]){"ls"},  0);
	lexer_test("ls -la", (const char *[]){"ls", "-la"},  0);
	lexer_test("ls -la | ", (const char *[]){"ls", "-la", "|"},  0);
	lexer_test("ls -la| ", (const char *[]){"ls", "-la", "|"},  0);
	lexer_test("|ls -la| ", (const char *[]){"|", "ls", "-la", "|"},  0);
	lexer_test("\"|ls -la| \"", (const char *[]){"\"|ls -la| \""},  0);
	lexer_test("'|ls -la|$ '", (const char *[]){"\'|ls -la|$ \'"},  0);
	lexer_test("\"\"\"\"'|ls -la|$ '", (const char *[]){"\"\"\"\"'|ls -la|$ '"},  0);
}
