/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   env.c                                           |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/04 13:34:35 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/05/04 13:34:35 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*envp_load_value(char *key)
{
	char	*value;

	value = ft_strchr(key, '=');
	if (value == NULL)
		value = ft_strdup("");
	else
	{
		*value = '\0';
		value = ft_strdup(++value);
	}
	if (value == NULL)
	{
		free(key);
		message_system_call_error("envp_load_key");
	}
	return (value);
}

int32_t	envp_load(t_dictionary *env, char **envp)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (!envp)
		return (SUCCESS);
	while (envp[i])
	{
		key = ft_strdup(envp[i++]);
		if (key == NULL)
			return (message_system_call_error("envp_load_key"));
		value = envp_load_value(key);
		if (value == NULL)
			return (message_system_call_error("envp_load_value"));
		if (dict_set(env, key, value) == ERROR)
		{
			free(value);
			free(key);
			return (message_system_call_error("dict_set"));
		}
		free(value);
		free(key);
	}
	return (SUCCESS);
}
