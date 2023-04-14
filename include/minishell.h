#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1
# define SUCCESS 0

# define CONTINUE 1
# define STOP 0

# ifndef DEBUG
#  define DEBUG 0
# endif

# define HASH_TABLE_SIZE 32

# define SHELDON "Sheldon"
# define E_SHELDON "sheldon: "
# define PROMPT "Sheldon$ "

# define NOT_FOUND 1

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <assert.h>

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

// Mininums
typedef enum e_status
{
	E_USAGE = 0,
	E_GENERAL = 1,
	E_BUILTIN = 2,
	E_EXEC = 126,
	E_COMMAND_NOT_FOUND = 127,
	E_EXIT_INVALID_ARG = 128,
	E_FATAL_SIGNAL = 128,
	E_CTRL_C = 130,
	E_UNKNOWN = 255,
	E_UNEXPECTED_TOKEN = 258,
	E_QUOTES = 259,
}					t_status;

typedef enum e_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}					t_type;

typedef enum e_signal_handler
{
	SREADLINE,
	SHEREDOC,
	SEXECUTOR
}					t_signal_handler;

// Ministructs
typedef struct s_pair
{
	char			*key;
	char			*value;
	struct s_pair	*next;
}					t_pair;

typedef struct s_expander
{
	bool			e_continue;
	bool			is_single;
	bool			is_double;
	char			*new_arg;
	t_list			*stack;
	t_list			*node;
	size_t			i;
}					t_expander;

typedef struct s_dictionary
{
	t_pair			*table[HASH_TABLE_SIZE];
	size_t			size;
}					t_dictionary;

typedef struct s_lexer
{
	t_list		*node;
	t_list		*tokens;
	size_t		token_count;
	size_t		meta_count;
	const char	*error_msg;
}				t_lexer;

typedef struct s_minishell
{
	t_dictionary	env;
	t_list			*ast;
	t_list			*tokens;
	char			*command_line;
	t_status		status;
	bool			stop;
	bool			is_pipeline;
}					t_minishell;

typedef struct s_redir
{
	char			*filename;
	t_type			type;
}					t_redir;

typedef struct s_command
{
	t_list			*arguments;
	t_list			*arguments_head;
	int32_t			n_arguments;
	t_list			*redirs;
	t_list			*redirs_head;
	int32_t			n_redirs;
}					t_command;

typedef struct s_command_table
{
	t_list			*commands_head;
	t_list			*commands;
	int32_t			n_commands;
}					t_command_table;

typedef struct s_builtin
{
	const char		*name;
	int				(*func)(char **arguments, t_minishell *shell);
}					t_builtin;


typedef struct
{
    const char *token;
    const char *error_msg;
} t_tokenerror;

// Main

int32_t			minishell(char **envp);
int32_t			init_handlers(void);
void				setup_signals(t_signal_handler handler);
void				reset_signals(void);

// Environment
int32_t			envp_load(t_dictionary *env, char **envp);

// Pair
void				pair_clean(t_pair *pair);
char				*pair_to_str(t_pair *pair);

// Dictionary
size_t			hash(char *str);
int32_t			dict_set(t_dictionary *dict, char *key, char *value);
char				*dict_get(t_dictionary *dict, char *key);
void				dict_delete(t_dictionary *dict, char *key);
void				dict_destroy(t_dictionary *dict);
void				dict_print(t_dictionary *dict);
char				**dict_to_envp(t_dictionary *dict);

// Lexer
t_list				*lexer(const char *command_line, t_status *status);
void					ft_skip_whitespaces(const char **input);
bool					quotes_even_or_odd(const char *str); // (by Lucien)
bool					check_lexical_conventions(const char *command, t_status *exit);
bool				check_meta_conventions(const char *command, const char **error_msg);
void 				lexer_initialize(t_lexer *lex);

// Parser
t_list				*parser(t_list *tokens, t_status *status, t_dictionary *env);
// Getters
void				get_one_command_table(t_list **ast, 
		t_command_table **command_table);
char				**get_arguments(t_command *cmd);
void				get_next_redir(t_command *cmd, t_redir **redir);
void				get_next_command(t_command_table *cmd, t_command **command);
char				**get_arguments(t_command *cmd);
// Constructers
t_list					*construct_ast(t_list *tokens, t_status *status, 
		t_dictionary *env);
t_command_table	*construct_command_table(t_list **tokens, t_status *status, 
		t_dictionary *env);
t_command				*construct_command(t_list **tokens, t_status *status, 
		t_dictionary *env);
t_redir					*construct_redir(t_list **tokens, t_status *status);
// Deconstructers
void				deconstruct_ast(t_list **ast);
void				deconstruct_command_table(void *ct);
void				deconstruct_command(void *command);
void				deconstruct_redirs(void *redir);
// Loggers
void				debug_ast(t_list *ast);
void				print_command_tables(t_list *command_table);
void				print_commands(t_command_table *command);
void				print_redirs(t_command *cmd);
void				print_arguments(t_command *cmd);

// Messages
const char		*message_lookup(t_status status);
t_status			message_system_call_error(const char *function_name);
void					message_signal(t_status signal_num);
t_status			message_child_status(t_status status);
t_status			message_general_error(t_status status, const char *msg);

// Minitypes
bool				is_pipe(int c);
bool				is_dollar(int c);
bool				is_meta(int c);
bool				is_redir(int c);
bool				is_quote(int c);
bool				is_double_quote(int c);
bool				is_single_quote(int c);
bool				is_quotechar(const char c);
bool				is_metachar(const char *str);
int32_t				metachar_len(const char *str);

// Expander
char				*expand_dollar(char *arg, size_t *i, t_status *status,
								   t_dictionary *env);
t_list				*expand_dollar_node(char *arg, size_t *i, t_status *status,
										  t_dictionary *env);
char				*expand_token(char *arg, t_status *status, t_dictionary *envd);
size_t				len_until_quote_or_dollar(char *str);

// Executor
int32_t				executor(t_minishell *shell);
bool				protected_dup2(int fd, t_type type);
bool				open_redir(char *path, t_type type);
int					is_dir(char *path);
char				**get_env_paths(t_dictionary *dict);
char				*check_env_paths(t_dictionary *dict, char *cmd);
char				*get_cmd_path(t_dictionary *dict, char *cmd);

// Builtins
int					ft_echo(char **arguments, t_minishell *shell);
int					ft_cd(char **arguments, t_minishell *shell);
int					ft_pwd(char **arguments, t_minishell *shell);
int					ft_export(char **arguments, t_minishell *shell);
int					ft_unset(char **arguments, t_minishell *shell);
int					ft_env(char **arguments, t_minishell *shell);
int 				ft_exit(char **args, t_minishell *shell);

#endif
