#include <minishell.h>

// void	expand_redirect_list(t_list *redirects, t_minishell *shell)
// {

// }

// Get the arguments and redirects out of the command structure so it can expand them if needed.
void	expand_cmd(t_command *cmd, t_minishell *shell)
{
	t_list	**arg_list;

	arg_list = &cmd->arguments;
	expand_argument_list(arg_list, shell);
	// expand_redirect_list(cmd->redirs, shell);
}

// loop over the command structures inside command table structure and start expanding for each.
void	expand_cmd_table(t_command_table *cmd_table, t_minishell *shell)
{
	t_command	*cmd;
	t_list		*iter;

	iter = cmd_table->commands;
	while (iter)
	{
		cmd = (t_command *)iter->content;
		expand_cmd(cmd, shell);
		iter = iter->next;
	}
}

/* The expander needs to expand $variable name and $? depending on the quoting.
	check if it is quoted.
	then check if it is double quoted.
	if it is double quoted expand if needed.
	single quotes do not have to be expanded.
	remove quotes.

	No quotes? and it is a $variable?
	Expand it into multiple arguments
*/
int32_t	expander(t_minishell *shell)
{
	t_command_table	*cmd_table;
	t_list			*ast;

	ast = shell->ast;
	while (ast)
	{
		cmd_table = (t_command_table *)ast->content;
		expand_cmd_table(cmd_table, shell);
		ast = ast->next;
	}
	return (SUCCESS);
}
