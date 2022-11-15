#ifndef BUILTINS
# define BUILTINS

#define NOBUILTIN = -1

typedef	struct s_builtin 
{
	const char *name;
	int (*builtin)(char **arguments, char **envp); //TODO turn into linked list to be able to change the content
}	t_builtin;

int ft_echo(char **arguments, char **envp);
int ft_cd(char **arguments, char **envp);
int ft_pwd(char **arguments, char **envp);
int ft_export(char **arguments, char **envp);
int ft_unset(char **arguments, char **envp);
int ft_env(char **arguments, char **envp);
int ft_exit(char **arguments, char **envp);

#endif
