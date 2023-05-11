/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   redirect_all_std.c                              |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:39:54 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:39:54 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <unit_test.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void redirect_stdin(void)
{
    cr_redirect_stdin();
}

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}
