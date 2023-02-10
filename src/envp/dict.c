#include <minishell.h>


void dict_init(t_dictionary *dict)
{
	dict->table = ft_calloc(HASH_TABLE_SIZE, sizeof(t_pair *));
}

size_t hash(char *str)
{
	size_t h;

	h = 0;
	while (*str)
	{
		h = h * 31 + *str;
		str++;
	}
	return (h % HASH_TABLE_SIZE);
}

void dict_set(t_dictionary *dict, char *key, char *value)
{
	size_t	index;
	t_pair *pair;

	index = hash(key) % HASH_TABLE_SIZE;
	pair = dict->table[index];
	while (pair != NULL && strcmp(pair->key, key) != 0) pair = pair->next;
	if (pair == NULL)
	{
		pair = malloc(sizeof(t_pair));
		pair->key = key;
		pair->next = dict->table[index];
		dict->table[index] = pair;
		dict->size++;
	}
	pair->value = value;
}

char *dict_get(t_dictionary *dict, char *key)
{
	size_t	index;
	t_pair *pair;

	index = hash(key) % HASH_TABLE_SIZE;
	pair = dict->table[index];
	while (pair != NULL)
	{
		if (strcmp(pair->key, key) == 0)
			return pair->value;
		pair = pair->next;
	}
	return (NULL);
}

void dict_delete(t_dictionary *dict, char *key)
{
	size_t	index;
	t_pair *pair;
	t_pair *prev;

	index = hash(key) % HASH_TABLE_SIZE;
	pair = dict->table[index];
	prev = NULL;
	while (pair != NULL)
	{
		if (strcmp(pair->key, key) == 0)
		{
			if (prev == NULL)
				dict->table[index] = pair->next;
			else
				prev->next = pair->next;
			free(pair);
			dict->size--;
			break;
		}
		prev = pair;
		pair = pair->next;
	}
}
