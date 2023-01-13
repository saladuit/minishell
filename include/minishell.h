#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <libft.h>
# include <errno.h>

/*
E_GENERAL:
	Miscellaneous errors, such as "divide by zero" and other
	impermissible operations,
E_BUILTIN:
	Missing keyword or command, or permission problem
	(and diff return code on a failed binary file comparison).
E_EXEC:
	Permission problem or command is not an executable
E_COMMAND_NOT_FOUND:
	Possible problem with $PATH or a typo
E_EXIT_INVALID_ARG:
	exit takes only integer args in the range 0 - 255
E_FATAL_SIGNAL:
	$? returns 137 (128 + 9)
E_CTRL_C:
	Control-C is fatal error signal 2, (130 = 128 + 2, see above)
E_EXIT_STATUS_OUT_OF_RANGE:
	exit takes only integer args in the range 0 - 255
*/
typedef enum e_exitcodes
{
	E_GENERAL = 1,
	E_BUILTIN = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_EXIT_STATUS_OUT_OF_RANGE = 225
}	t_exitcodes;

typedef enum e_message
{
	SUCCESS,
	USAGE,
	PROMPT,
	EMALLOC,
	EREQUEST,
	ETYPE,
}	t_message;

typedef enum e_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_type;

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

typedef struct s_command
{
	t_list	*arguments;
	t_list	*redirs;
}	t_command;

typedef struct s_command_table
{
	int32_t	command_count;
	t_list	*commands;
}	t_command_table;

typedef struct s_builtin
{
	const char *name;
	int (*func)(char **arguments, t_minishell *shell); //TODO turn into linked list to be able to change the content. NOOOOOO pls no linked list
}	t_builtin;


// Main

int32_t			minishell(t_minishell *shell);
int32_t			init_handlers(void);
int32_t			ft_minishell_exit(t_message code);
char			**dup_envp(char **envp);
void			setup_signals(void);
void			reset_signals(void);

// Messages

const char		*messages_lookup(t_message code);

// Minitypes

bool			is_delimiter(int c);
bool			is_redir(int c);
bool			is_metachar(int c);
bool			is_quote(int c);
bool			is_double_quote(int c);
bool			is_double_quoted(char *str);
bool			is_single_quote(int c);
bool			is_single_quoted(char *str);
bool			is_expand(int c);

// Lexer

int32_t			lexer(const char *command_line, t_list **tokens);

// Expander

int32_t			expander(t_minishell *shell);
char			*ft_strjoin_free_free(char *expanded, char *tmp);
int32_t			check_expand(char *str);
bool			needs_expanding(char *str);
bool			valid_varchar(char c);
void			expand_argument_list(t_list **arg_list, t_minishell *shell);
int32_t			skip_single_quotes(char *str);
int32_t			skip_double_quotes(char *str);
int32_t			skip_variable_name(char *str);
int32_t			skip_whitespace(char *str);
int32_t			find_var_start(char *str, int32_t index);
char			*expand_variables(char *str, t_minishell *shell);
char			**split_words(char *str);
t_list			*pop_node(t_list **list, t_list *pop_node);

// Executor

int32_t			execute(char *command_path, char **args, char **envp);
int32_t			executor(t_minishell *shell);
bool			protected_dup2(int fd, t_type type);
bool			open_redir(char *path, t_type type);
char			*get_redir_file(t_command *command, t_type type);
int				is_dir(char *path);
char			**get_env_paths(char **envp);
char			*check_env_paths(char **envp, char *cmd);
char			*get_cmd_path(char **envp, char *cmd);

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
t_list			*parser(t_list *tokens);

/**
 * @brief Constructs a command from
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */
t_command		*construct_command(t_list **tokens);

char			**get_arguments(t_command *cmd);
t_redir			*get_next_redir(t_command *cmd);
t_command*		get_next_command(t_command_table *cmdt);
t_command_table *get_next_command_table(t_list **ast);

/**
 * @brief Returns a Command Table  made from the tokens provides.
 * Exits on failure
 *
 * @param ast		-	Abstract Syntax Tree to iterate over
 * @return 			-	Constructed Command Table
 */
t_command_table	*construct_command_table(t_list **tokens);

/*
 * @brief contructs a redirection struct out of two tokens
 * the first token will become the redirection type and the second
 * will become the filname
 *
 * @param command	-	Linked list with tokens
 * @return 			-	Redirection struct
 */

t_redir			*construct_redir(t_list **tokens);

/**
 * @brief Returns the current command and iterates to the next one for future use
 * Exits on failure
 *
 * @param command	-	Commands to iterate over
 * @return 			-	NULL to indicate end of list
 */
t_list			*construct_ast(t_list *tokens);

// Builtins

int				ft_echo(char **arguments, t_minishell *shell);
int				ft_cd(char **arguments, t_minishell *shell);
int				ft_pwd(char **arguments, t_minishell *shell);
int				ft_export(char **arguments, t_minishell *shell);
int				ft_unset(char **arguments, t_minishell *shell);
int				ft_env(char **arguments, t_minishell *shell);
int				ft_exit(char **arguments, t_minishell *shell);

#endif
