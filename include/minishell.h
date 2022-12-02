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

#endif
