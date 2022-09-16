/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   push_swap_tester.c                              |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/27 14:45:57 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/19 20:57:50 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

Test(argv_checker, fixed)
{
	argv_checker_test(1, ((const char *[]){""}), false);
	argv_checker_test(1, ((const char *[]){"1"}), true);
	argv_checker_test(1, ((const char *[]){"a"}), false);

	argv_checker_test(2, ((const char *[]){"1", "2"}), true);
	argv_checker_test(2, ((const char *[]){"1", "+2"}), true);
	argv_checker_test(1, ((const char *[]){"10+-"}), false);
	argv_checker_test(9, ((const char *[]){"1", "2", "3", "4", "5", "6", "7", "8", "9"}), true);
	argv_checker_test(2, ((const char *[]){"1", "a"}), false);
	argv_checker_test(2, ((const char *[]){"1", "1a"}), false);
	argv_checker_test(2, ((const char *[]){"1", "\n"}), false);
	argv_checker_test(2, ((const char *[]){"1", " 2"}), false);
	argv_checker_test(2, ((const char *[]){"1", " "}), false);
}

Test(array_check, fixed)
{
	array_check_test(1, ((const int []){0}), SORTED);
	array_check_test(2, ((const int []){0, 1}), SORTED);
	array_check_test(2, ((const int []){1, 0}), NOT_SORTED);
	array_check_test(2, ((const int []){0, 0}), DOUBLE);
}

Test(init_integer_array_test, fixed)
{
	init_integer_array_test(1, ((const char *[]){"1"}), ((const int []){1}));
	init_integer_array_test(1, ((const char *[]){"+2147483648"}), NULL);
	init_integer_array_test(1, ((const char *[]){"0"}), ((const int []){0}));
	init_integer_array_test(1, ((const char *[]){"-00"}), ((const int []){0}));
	init_integer_array_test(1, ((const char *[]){"+00"}), ((const int []){0}));
	init_integer_array_test(1, ((const char *[]){"00-"}), NULL);
	init_integer_array_test(1, ((const char *[]){"000001"}), ((const int []){1}));
	init_integer_array_test(1, ((const char *[]){"+2147483647"}), ((const int []){2147483647}));
	init_integer_array_test(1, ((const char *[]){"--+2147483647"}), NULL);
	init_integer_array_test(1, ((const char *[]){"-2147483648"}), ((const int []){-2147483648}));
	init_integer_array_test(1, ((const char *[]){"+-2147483648"}), NULL);
	init_integer_array_test(1, ((const char *[]){"2147483648"}), NULL);
	init_integer_array_test(2, ((const char *[]){"1", "2"}), ((const int []){1, 2}));
}

Test(make_positive, fixed)
{
	make_positive_test(1, ((int []){-1}), ((const int []){0}));
	make_positive_test(2, ((int []){-1, -500}), ((const int []){1, 0}));
	make_positive_test(5, ((int []){40, -10, -5, 0, -1}), ((const int []){4, 0, 1, 3, 2}));
	make_positive_test(3, ((int []){2, 3, 1}), ((const int []){1, 2, 0}));
}
1 2 3

Test(init_stack, fixed)
{
	init_stack_test(2, ((const int []){1, 2}));
}

////////////////////////////////////////////////////////////////////////////////
//			PROGRAM
////////////////////////////////////////////////////////////////////////////////
Test(push_swap, fixed)
{
	push_swap_test(1, ((const char *[]){"1"}), true);
	push_swap_test(1, ((const char *[]){"-2147483649"}), false);
	push_swap_test(2, ((const char *[]){"2", "1"}), true);
	push_swap_test(2, ((const char *[]){"1", "1"}), false);
	push_swap_test(2, ((const char *[]){"99999999999999999999", "1"}), false);
}
