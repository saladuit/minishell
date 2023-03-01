#include <unit_test.h>

/*******************************************************************************/
/*                           Is_pipe                                           */
/*******************************************************************************/

bool	is_pipe(int c);

Test(is_pipe, basic)
{
  cr_assert(is_pipe('|') == true);
}

Test(is_pipe, upper_boundary)
{
  cr_assert(is_pipe('|' + 1) == false);
}

Test(is_pipe, lower_boundary)
{
  cr_assert(is_pipe('|' - 1) == false);
}

/*******************************************************************************/
/*                           Is_dollar                                         */
/*******************************************************************************/

bool	is_dollar(int c);

Test(is_dollar, basic)
{
  cr_assert(is_dollar('$') == true);
}

Test(is_dollar, upper_boundary)
{
  cr_assert(is_dollar('$' + 1) == false);
}

Test(is_dollar, lower_boundary)
{
  cr_assert(is_dollar('$' - 1) == false);
}

/*******************************************************************************/
/*                           Is_double_quote                                   */
/*******************************************************************************/

bool	is_double_quote(int c);

Test(is_double_quote, basic)
{
  cr_assert(is_double_quote('\"') == true);
}

Test(is_double_quote, upper_boundary)
{
  cr_assert(is_double_quote('\"' + 1) == false);
}

Test(is_double_quote, lower_boundary)
{
  cr_assert(is_double_quote('\"' - 1) == false);
}

/*******************************************************************************/
/*                           Is_redir                                   */
/*******************************************************************************/

bool	is_redir(int c);

Test(is_redir, input_basic)
{
  cr_assert(is_redir('<') == true);
}

Test(is_redir, input_upper_boundary)
{
  cr_assert(is_redir('<' + 1) == false);
}

Test(is_redir, input_lower_boundary)
{
  cr_assert(is_redir('<' - 1) == false);
}

Test(is_redir, output_basic)
{
  cr_assert(is_redir('>') == true);
}

Test(is_redir, output_upper_boundary)
{
  cr_assert(is_redir('>' + 1) == false);
}

Test(is_redir, output_lower_boundary)
{
  cr_assert(is_redir('>' - 1) == false);
}

/*******************************************************************************/
/*                           Is_single_quote                                   */
/*******************************************************************************/

bool	is_single_quote(int c);

Test(is_single_quote, basic)
{
  cr_assert(is_single_quote('\'') == true);
}

Test(is_single_quote, upper_boundary)
{
  cr_assert(is_single_quote('\'' + 1) == false);
}

Test(is_single_quote, lower_boundary)
{
  cr_assert(is_single_quote('\'' - 1) == false);
}
