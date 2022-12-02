#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

# include <libft.h>


typedef struct s_minishell
{
	char	**env;
	int32_t	exit_code;
	t_list	*ast;
	t_list	*tokens;

}	t_minishell;

char	**dup_envp(char **envp);
int32_t	init_handlers(void);
int32_t	minishell(t_minishell *shell);

#endif
