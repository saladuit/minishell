/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_tree.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 14:53:16 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 17:12:52 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <ft_tree.h>

void	add_tree_node(t_tree **tree, void *data)
{
	t_tree *tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_tree));
	(void)data;	
	(void)tree;
}
void	print_tree(t_tree *tree)
{
	(void)tree;
}
void	delete_tree(t_tree *tree)
{
	(void)tree;
}
