#include "unit_test.h"

//Test(so_long, fixed_tests)
//{
//	so_long_helper(1, (const char *[]){"1"}, true);
//}

//Test(minishell, fixed_tests)
//{
//	minishell_test(NULL, 0, EXIT_SUCCESS);
//}

// Test(lexer, valid_input)
// {
// 	lexer_test("ls", (const char *[]){"ls"}, 0);
// 	lexer_test("ls -la", (const char *[]){"ls", "-la"}, 0);
// 	lexer_test("ls -la | ", (const char *[]){"ls", "-la", "|"}, 0);
// 	lexer_test("ls -la| ", (const char *[]){"ls", "-la", "|"}, 0);
// 	lexer_test("|ls -la| ", (const char *[]){"|", "ls", "-la", "|"}, 0);
// 	lexer_test("\"|ls -la| \"", (const char *[]){"\"|ls -la| \""}, 0);
// 	lexer_test("'|ls -la|$ '", (const char *[]){"\'|ls -la|$ \'"}, 0);
// 	lexer_test("\"\"\"\"'|ls -la|$ '", (const char *[]){"\"\"\"\"'|ls -la|$ '"}, 0); // Repeating quotes
// 	lexer_test("'|ls -la|$", (const char *[]){"\'|ls -la|$"}, 0);
// }

Test(tokenizer, valid_input)
{
	tokenizer_test("ls", (const char *[]){"ls"},  0);
	tokenizer_test("ls -la", (const char *[]){"ls", "-la"},  0);
	tokenizer_test("ls -la | ", (const char *[]){"ls", "-la", "|"},  0);
	tokenizer_test("ls -la| ", (const char *[]){"ls", "-la", "|"},  0);
	tokenizer_test("|ls -la| ", (const char *[]){"|", "ls", "-la", "|"},  0);
	tokenizer_test("\"|ls -la| \"", (const char *[]){"\"|ls -la| \""},  0);
	tokenizer_test("'|ls -la|$ '", (const char *[]){"\'|ls -la|$ \'"},  0);
	tokenizer_test("\"\"\"\"'|ls -la|$ '", (const char *[]){"\"\"\"\"'|ls -la|$ '"},  0);
	tokenizer_test("'|ls -la|$", (const char *[]){"\'|ls -la|$"}, 0);
	tokenizer_test("|", (const char *[]){"|"}, 0);
	tokenizer_test("<", (const char *[]){"<"}, 0);
	tokenizer_test(">", (const char *[]){">"}, 0);
	tokenizer_test("<<", (const char *[]){"<", "<"}, 0);
	tokenizer_test(">>", (const char *[]){">", ">"}, 0);
	tokenizer_test("||", (const char *[]){"|", "|"}, 0);
	tokenizer_test("\"\"", (const char *[]){"\"\""}, 0);
	tokenizer_test("''", (const char *[]){"''"}, 0);
	tokenizer_test("a<a", (const char *[]){"a", "<", "a"}, 0);
	tokenizer_test("a  < a ", (const char *[]){"a", "<", "a"}, 0);
	tokenizer_test("\"|\"", (const char *[]){"\"|\""}, 0);
	tokenizer_test("", (const char *[]){NULL}, 0);
	}

Test(analyzer, valid_input)
{
	lexer_test("ls", (const char *[]){"ls"}, 0);
	lexer_test("ls -la", (const char *[]){"ls", "-la"}, 0);
	lexer_test("ls -la | ", (const char *[]){"ls", "-la", "|"}, 0);
	lexer_test("ls -la| ", (const char *[]){"ls", "-la", "|"}, 0);
	lexer_test("|ls -la| ", (const char *[]){"|", "ls", "-la", "|"}, 0);
	lexer_test("\"|ls -la| \"", (const char *[]){"\"|ls -la| \""}, 0);
	lexer_test("'|ls -la|$ '", (const char *[]){"\'|ls -la|$ \'"}, 0);
	lexer_test("\"\"\"\"'|ls -la|$ '", (const char *[]){"\"\"\"\"'|ls -la|$ '"}, 0);
}
