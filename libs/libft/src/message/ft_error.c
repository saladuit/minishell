/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 09:58:37 by dritsema      #+#    #+#                 */
/*   Updated: 2022/09/16 10:08:54 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
}
