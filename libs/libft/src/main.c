/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   main.c                                                               0   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2021/10/13 14:05:27 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/02/09 21:27:40 by safoh                                0   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

/*void			lstdelone_f(void *d) {
	free(d);
}*/

void			lstiter_f(void *content) {
	char *s = content;

	s[0] = 'O';
	s[1] = 'K';
}
int	main()
{
	t_list	*l = ft_lstnew(ft_strdup("KO !"));
	l->next = ft_lstnew(ft_strdup("KO !"));
	l->next->next = ft_lstnew(ft_strdup("KO !"));
	ft_lstiter(l, lstiter_f);
	return (0);
}
