/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/16 21:15:45 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/16 14:50:10 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

//Test(so_long, fixed_tests)
//{
//	so_long_helper(1, (const char *[]){"1"}, true);
//}

//Test(minishell, fixed_tests)
//{
//	minishell_test(NULL, 0, EXIT_SUCCESS);
//}

Test(lexer, fixed_tests)
{
	lexer_test("ls -la", (const char *[]){"ls", "-la"},  0);
	lexer_test("\"hoi\" wat", (const char *[]){"hoi", "wat"},  0);
}
