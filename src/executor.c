/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: safoh <safoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 16:19:58 by safoh         #+#    #+#                 */
/*   Updated: 2022/09/19 18:01:32 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <message.h>
#include <command.h>
#include <unistd.h>
#include <libft.h>

char	**get_args(t_command_table *command_table)
{
	char		**args;
	t_command	*command;
	t_list		*tokens;
	int32_t		i;

	command = (t_command *)command_table->commands->content;
	args = malloc(command->arg_count + 1);
	tokens = command->tokens;
	i = 0;
	while (i < command->arg_count)
	{
		args[i] = tokens->content;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

pid_t	execute(char **args, char **envp)
{
	pid_t	pid;

	(void)envp;
	pid = fork();
	if (pid != 0)
		return (pid);
	execv(args[0], args);
	_Exit(EXIT_FAILURE);
}

int32_t	executor(t_list *abstract_syntax_tree)
{
	t_command_table	*command_table;
	char			**args;
	char			*envp[] = {"", NULL};

	command_table = (t_command_table *)abstract_syntax_tree->content;
	args = get_args(command_table);
	execute(args, envp);
	return (SUCCESS);
}
