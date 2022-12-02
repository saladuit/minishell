#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdint.h>
# include <minishell.h>

bool	valid_varchar(char c);
int32_t	check_expand(char *str);
char	*strjoin_free_free(char *expanded, char *tmp);
int32_t	expander(t_minishell *shell);

#endif
