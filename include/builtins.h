
#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>

typedef struct s_builtin
{
	const char *name;
	int (*func)(char **arguments, t_minishell *shell); //TODO turn into linked list to be able to change the content. NOOOOOO pls no linked list
}	t_builtin;

int	ft_echo(char **arguments, t_minishell *shell);
int	ft_cd(char **arguments, t_minishell *shell);
int	ft_pwd(char **arguments, t_minishell *shell);
int	ft_export(char **arguments, t_minishell *shell);
int	ft_unset(char **arguments, t_minishell *shell);
int	ft_env(char **arguments, t_minishell *shell);
int	ft_exit(char **arguments, t_minishell *shell);

#endif
