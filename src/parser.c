#include "command.h"
#include "libft.h"
#include "message.h"
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	ft_ismetachar(const char meta_c)
{
	if (meta_c == '>' || meta_c == '<' || meta_c == '|')
		return (true);
	return (false);
}

bool	ft_isredir(const char redir)
{
	if (redir == '>' || redir == '<')
		return (true);
	return (false);
}

bool	ft_isdelimiter(const char sep)
{
	if (sep == '|')
		return (true);
	return (false);
}

t_list	*ft_lstadd_backnew(t_list **lst, void *content)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(lst, new_node);
	return (new_node);
}

int32_t	ft_matrixclear(char ***string)
{
	size_t	i;

	i = 0;
	if (!*string)
		return (ERROR);
	while ((*string)[i])
	{
		free((*string)[i]);
		i++;
	}
	free(*string);
	*string = NULL;
	return (ERROR);
}

int32_t	fill_arguments(t_command *command, t_list **arg_list)
{
	size_t	i;

	command->arguments = ft_calloc(command->arg_count + 1, sizeof(char *));
	if (!command->arguments)
		return (ERROR);
	i = 0;
	while (*arg_list)
	{
		command->arguments[i] = ft_strdup((*arg_list)->content);
		if (!command->arguments[i])
			return (ft_matrixclear(&command->arguments));
		arg_list = &(*arg_list)->next;
		i++;
	}
	return (SUCCESS);
}

t_redir	*construct_redir(t_list **tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (!ft_strncmp("<", (*tokens)->content, 2))
		redir->type = INPUT;
	if (!ft_strncmp("<<", (*tokens)->content, 3))
		redir->type = HEREDOC;
	if (!ft_strncmp(">", (*tokens)->content, 2))
		redir->type = OUTPUT;
	if (!ft_strncmp(">>", (*tokens)->content, 3))
		redir->type = APPEND;
	*tokens = (*tokens)->next;
	redir->filename = ft_strdup((*tokens)->content);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	return (redir);
}

t_list	*deconstruct_redir(t_redir **redir)
{
	if ((*redir)->filename)
	{
		free((*redir)->filename);
		(*redir)->filename = NULL;
	}
	if (*redir)
	{
		free(*redir);
		*redir = NULL;
	}
	return (NULL);
}

t_list	*add_redir(t_list **tokens, t_list **redir)
{
	t_list	*new_node;
	t_redir	*new_redir;

	new_redir = construct_redir(tokens);
	if (!new_redir)
		return (NULL);
	new_node = ft_lstadd_backnew(redir, new_redir);
	if (!new_node)
		return (deconstruct_redir(&new_redir));
	*tokens = (*tokens)->next;
	return (new_node);
}

t_list	*add_argument(t_list **tokens, t_command *command, t_list **arguments)
{
	t_list	*new_node;
	char	*argument;

	argument = ft_strdup((*tokens)->content);
	if (!argument)
		return (NULL);
	new_node = ft_lstadd_backnew(arguments, argument);
	if (!new_node)
	{
		free(argument);
		return (NULL);
	}
	command->arg_count++;
	*tokens = (*tokens)->next;
	return (new_node);
}

t_command	*deconstruct_command(t_command **command)
{
	ft_matrixclear(&(*command)->arguments);
	ft_lstclear(&(*command)->redir, free);
	free(*command);
	*command = NULL;
	return (NULL);
}

t_command	*clear_get_command(t_command **command, t_list **arguments)
{
	deconstruct_command(command);
	ft_lstclear(arguments, free);
	return (NULL);
}

t_command	*get_command(t_list **tokens)
{
	t_command	*command;
	t_list		*arguments;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	arguments = NULL;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (ft_isdelimiter(*token))
			break ;
		if (ft_isredir(*token) && !add_redir(tokens, &command->redir))
			return (clear_get_command(&command, &arguments));
		else if (!add_argument(tokens, command, &arguments))
			return (clear_get_command(&command, &arguments));
	}
	if (fill_arguments(command, &arguments) == ERROR)
		return (clear_get_command(&command, &arguments));
	return (command);
}

t_command_table	*get_command_table(t_list **tokens)
{
	t_command_table	*command_table;

	command_table = ft_calloc(1, sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	while (*tokens)
		if (!ft_lstadd_backnew(&command_table->commands, get_command(tokens)))
		{
			ft_lstclear(&command_table->commands, free);
			free(command_table);
			return (NULL);
		}
	return (command_table);
}

t_list	*get_abstract_syntax_tree(t_list *tokens)
{
	t_list	*abstract_syntax_tree;

	abstract_syntax_tree = NULL;
	while (tokens)
		if (!ft_lstadd_backnew(&abstract_syntax_tree, \
					(void *)get_command_table(&tokens)))
		{
			ft_lstclear(&abstract_syntax_tree, free);
			return (NULL);
		}
	return (abstract_syntax_tree);
}

int32_t parser(t_list **abstract_syntax_tree, t_list *tokens)
{
	*abstract_syntax_tree = get_abstract_syntax_tree(tokens);
	if (!*abstract_syntax_tree)
		return (ERROR);
	return (SUCCESS);
}
