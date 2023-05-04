/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   pair.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:34:40 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:34:40 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pair_clean(t_pair *pair)
{
	if (pair->key)
	{
		free(pair->key);
		pair->key = NULL;
	}
	if (pair->value)
	{
		free(pair->value);
		pair->value = NULL;
	}
	free(pair);
	pair = NULL;
}

char	*pair_to_str(t_pair *pair)
{
	char	*str;
	size_t	length;

	length = ft_strlen(pair->key) + ft_strlen(pair->value) + 2;
	str = ft_calloc(length, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, pair->key, length);
	ft_strlcat(str, "=", length);
	ft_strlcat(str, pair->value, length);
	return (str);
}
