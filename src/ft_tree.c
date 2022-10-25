/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tree.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 14:53:16 by safoh         #+#    #+#                 */
/*   Updated: 2022/10/25 16:03:46 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_tree.h>
#include <stdlib.h>

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
