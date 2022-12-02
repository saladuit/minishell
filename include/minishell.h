#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

# include <libft.h>

// Ministructs

typedef struct s_minishell
{
	char	**env;
	char	**export;
	int32_t	exit_code;
	t_list	*ast;
	t_list	*tokens;

}	t_minishell;

typedef struct s_redir
{
	char	*filename;
	t_type	type;
}	t_redir;

// Mini_Enums

typedef enum e_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_type;



char	**dup_envp(char **envp);
int32_t	init_handlers(void);
int32_t	minishell(t_minishell *shell);
void	setup_signals(void);

// Minitypes

bool	is_delimiter(int c);
bool	is_redir(int c);
bool	is_metachar(int c);
bool	is_quote(int c);
bool	is_double_quote(int c);
bool	is_double_quoted(char *str);
bool	is_single_quote(int c);
bool	is_single_quoted(char *str);
bool	is_expand(int c);

/**
 *  @brief Converts tokens into an Abstract Syntax Tree.
 *  Exits program on failure.
 *
 *  An Abstract Syntax Tree is a linked list of chained command tables.
 *  Each command table is delimited by:
 *  - ;
 *  - &&
 *  - ||
 *  A command table contains a counter to keep track of the amount of commands
 *  and a linked list of commands.
 *
 *  A command consists out of arguments and redirections and
 *  a counter for the amount of arguments.
 *
 *  The redirections have their own structure containing a filename and type.
 *
 *  The Data Structures used are defined in command_table.h & command.h respectively.
 *
 *  The parser provides interfaces to better communicate with this data structure.
 *  These are defined in the astapi.h
 *  - Iterating to the next command table.
 *  - Iterating to the next command.
 *  - Getting the command arguments.
 *  - Getting the next redirection struct.
 *
 *  @param ast		-	Empty linked list
 *  @param tokens	-	The tokens to be placed incside the AST
 *
 *  @return 		- The constructed AST
 */
t_list	*parser(t_list *tokens);

/*
 * @brief contructs a redirection struct out of two tokens
 * the first token will become the redirection type and the second
 * will become the filname
 *
 * @param command	-	Linked list with tokens
 * @return 			-	Redirection struct
 */

t_redir	*construct_redir(t_list **tokens);

#endif
