/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dict_destroy.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 17:31:19 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 17:31:19 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dict_destroy(t_dictionary *dict)
{
	size_t	i;
	t_pair	*next;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		while (dict->table[i])
		{
			next = dict->table[i]->next;
			pair_clean(dict->table[i]);
			dict->table[i] = next;
		}
		i++;
	}
}
