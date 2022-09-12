/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 02:45:37 by saladin       #+#    #+#                 */
/*   Updated: 2022/03/31 18:50:34 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ft_isprint(int c)
{
	if ((unsigned int)c >= 32 && (unsigned int)c <= 126)
		return (1);
	else
		return (0);
}
