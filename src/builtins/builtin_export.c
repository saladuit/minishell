/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-bus <lvan-bus@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 19:07:06 by lvan-bus      #+#    #+#                 */
/*   Updated: 2023/05/04 19:07:07 by lvan-bus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_value(char *key)
{
	char *value;

	value = NULL;
	if (*key == '=')
		return (ft_strdup(""));
	value = ft_strchr(key, '=');
	if (value == NULL)
		return (ft_strdup(""));
	*value = '\0';
	return (ft_strdup(++value));
}

bool	validate_alpha(char *arg, t_status *status)
{
	if ((ft_isalpha(arg[0]) == false && arg[0] != UNDERSCORE) || ft_strbapi(arg, is_alnumunderscore) == false)
	{
		export_error_msg_not_valid(arg, status);
		return (false);
	}
	return (true);
}

void	ft_export(char **arguments, t_minishell *shell)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 1;
	while (arguments[i] != NULL)
	{
		key = ft_strdup(arguments[i]);
		if (key == NULL)
		{
			shell->status = message_system_call_error("export: ");
			return ;
		}
		value = get_value(key);
		if (!value)
		{
			free(key);
			shell->status = message_system_call_error("export: ");
			return ;
		}
		if (!validate_alpha(key, &shell->status))
		{
			i++;
			free(key);
			free(value);
			continue ;
		}
		if (dict_set(&shell->env, key, value) == ERROR)
		{
			free(key);
			free(value);
			shell->status = message_system_call_error("export: ");
			return ;
		}
		i++;
	}
}
