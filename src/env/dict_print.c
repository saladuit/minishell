/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dict_print.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 17:48:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 17:48:38 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void dict_print(t_dictionary *dict, int fd)
{
	size_t	i;
	t_pair *pair;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		pair = dict->table[i];
		while (pair && ft_strlen(pair->key) > 0)
		{
			put_builtin(pair->key, fd);
			put_builtin(pair->value, fd);
			put_builtin("\n", fd);
			pair = pair->next;
		}
		i++;
	}
}
