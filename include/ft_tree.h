/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_tree.h                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/09/13 16:22:28 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/09/13 16:28:24 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H

typedef struct	s_tree
{
	void *data;
	struct s_tree *left;
	struct s_tree *right;
}	t_tree;

void	add_tree_node(t_tree **tree, void *data);
void	delete_tree(t_tree *tree);
#endif
