#include <minishell.h>

#define HASH_TABLE_SIZE 32

void dict_init(Dictionary *dict)
{
	dict->size = 0;
	dict->table = (Pair**)malloc(HASH_TABLE_SIZE * sizeof(Pair*));
	memset(dict->table, 0, HASH_TABLE_SIZE * sizeof(Pair*));
}

size_t hash(char *str) 
{
	size_t	h;

	h = 0;
	while (*str)
	{
		h = h * 31 + *str;
		str++;
	}
	return (h % HASH_TABLE_SIZE);
}

void dict_set(Dictionary *dict, char *key, char *value) 
{
	size_t index;
	Pair *pair;

	index = hash(key) % HASH_TABLE_SIZE;
	pair = dict->table[index];
  while (pair != NULL && strcmp(pair->key, key) != 0) 
    pair = pair->next;
  if (pair == NULL)
  {
    pair = malloc(sizeof(Pair));
    pair->key = key;
    pair->next = dict->table[index];
    dict->table[index] = pair;
    dict->size++;
  }
  pair->value = value;
}

char *dict_get(Dictionary *dict, char *key) 
{
	size_t index;
	Pair *pair;

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

void dict_delete(Dictionary *dict, char *key) 
{
	size_t	index;
	Pair	*pair;
	Pair	*prev;

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
