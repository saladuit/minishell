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

char	**dict_to_envp(t_dictionary *dict)
{
	char	**envp;
	size_t	i;
	size_t	j;
	t_pair	*iter;

	envp = ft_calloc(dict->size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < HASH_TABLE_SIZE)
	{
    iter = dict->table[i];
    while (iter)
    {
      envp[j] = pair_to_str(iter);
      if (envp[j] == NULL)
      {
        ft_matrixfree(&envp);
        return (NULL);
      }
      iter = iter->next;
      j++;
    }
    i++;
	}
	return (envp);
}

void	dict_print(t_dictionary *dict)
{
	size_t	i;
	t_pair	*pair;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		pair = dict->table[i];
		while (pair && ft_strlen(pair->key) > 0)
		{
			printf("%s=%s\n", pair->key, pair->value);
			pair = pair->next;
		}
		i++;
	}
}

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

void dict_delete(t_dictionary *dict, char *key)
{
  size_t index;
  t_pair *iter;
  t_pair *prev;

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
		free(pair->value);
	if (pair == NULL)
	{
		pair = ft_calloc(1, sizeof(t_pair));
		if (!pair)
			return (ERROR);
		pair->key = ft_strdup(key);
		if (!pair->key)
			return (pair_clean(pair), ERROR);
		pair->next = dict->table[index];
		dict->table[index] = pair;
		dict->size++;
	}
	pair->value = ft_strdup(value);
	if (!pair->value)
	{
		dict->table[index] = NULL;
		return (pair_clean(pair), ERROR);
	}
	return (SUCCESS);
}
