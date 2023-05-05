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

static void	get_value(char **value, char *key)
{
	*value = ft_strchr(key, '=');
	if (*value == NULL)
		*value = ft_strdup("");
	else
	{
		**value = '\0';
		*value = ft_strdup(++(*value));
	}
}

static void	initialize_export(bool *ret, size_t *i)
{
	*ret = false;
	*i = 1;
}

void	ft_export(char **arguments, t_minishell *shell)
{
	char	*key;
	char	*value;
	size_t	i;
	bool	ret;

	initialize_export(&ret, &i);
	validate_arg(arguments[i], &ret);
	while (arguments[i] != NULL && ret == false)
	{
		if (!validate_alpha(arguments[i], &i, &shell->status))
			continue ;
		key = ft_strdup(arguments[i]);
		if (key == NULL)
		{
			export_error_msg_out_of_memory(shell, &i, &ret);
			return ;
		}
		get_value(&value, key);
		if (!value)
			export_error_msg_out_of_memory(shell, &i, &ret);
		dict_set(&shell->env, key, value);
		if (!validate_dict(shell, key, &i, &ret))
			return ;
		i++;
	}
}
