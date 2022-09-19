#include <unit_test.h>

Test(execute, valid_input)
{
	execute_test("/bin/ls", (char *[]){"/bin/ls"}, (char *[]){""}, 0);
}
