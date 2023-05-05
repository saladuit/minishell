/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dict_to_envp.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 17:31:15 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 17:31:15 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int32_t	process_hash_table_entry(t_pair *iter, char **envp, size_t *j)
{
	while (iter)
	{
		envp[*j] = pair_to_str(iter);
		if (envp[*j] == NULL)
		{
			ft_matrixfree(&envp);
			return (ERROR);
		}
		iter = iter->next;
		(*j)++;
	}
	return (SUCCESS);
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
		if (process_hash_table_entry(iter, envp, &j) == ERROR)
			return (NULL);
		i++;
	}
	return (envp);
}
