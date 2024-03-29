/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   is_undersquare.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/11 14:07:55 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/11 14:07:55 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_alnumunderscore(int c)
{
	return (c == '_' || isalnum(c));
}
