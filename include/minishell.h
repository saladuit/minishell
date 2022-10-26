#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>


int32_t	init_handlers(void);
int32_t	minishell(char **envp);

#endif
