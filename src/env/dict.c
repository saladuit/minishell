/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dict.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:32:50 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:32:50 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	hash(char *str)
{
	size_t	h;

	h = 0;
	while (*str)
	{
		h = h * (HASH_TABLE_SIZE - 1) + *str;
		str++;
	}
	return (h % HASH_TABLE_SIZE);
}

void	dict_remove_pair(t_dictionary *dict, char *key)
{
	size_t	index;
	t_pair	*iter;
	t_pair	*prev;

	index = hash(key);
	iter = dict->table[index];
	prev = NULL;
	while (iter != NULL)
	{
		if (ft_strncmp(iter->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				dict->table[index] = iter->next;
			else
				prev->next = iter->next;
			pair_clean(iter);
			dict->size--;
			return ;
		}
		prev = iter;
		iter = iter->next;
	}
}

char	*dict_get(t_dictionary *dict, char *key)
{
	size_t	index;
	t_pair	*pair;

	index = hash(key);
	pair = dict->table[index];
	while (pair != NULL)
	{
		if (ft_strncmp(pair->key, key, ft_strlen(key) + 1) == 0)
			return (pair->value);
		pair = pair->next;
	}
	return (NULL);
}

int32_t	dict_set(t_dictionary *dict, char *key, char *value)
{
	size_t	index;
	t_pair	*pair;

	index = hash(key);
	pair = dict->table[index];
	while (pair && ft_strncmp(pair->key, key, ft_strlen(key) + 1) != 0)
		pair = pair->next;
	if (pair)
	{
		free(pair->value);
		pair->value = ft_strdup(value);
		if (!pair->value)
			return (pair_clean(pair), ERROR);
	}
	else
	{
		pair = create_pair(key, value, dict->table[index]);
		if (!pair)
			return (ERROR);
		dict->table[index] = pair;
		dict->size++;
	}
	return (SUCCESS);
}
