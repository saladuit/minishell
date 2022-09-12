/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: saladin <saladin@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 17:29:41 by saladin       #+#    #+#                 */
/*   Updated: 2022/04/12 14:24:29 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define FT_LONG_MAX 9223372036854775807

//WRITE FUNCTIONS
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putuint_fd(unsigned int nb, int fd);

//CHECK FUNCTIONS
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);
bool	ft_isspace(int c);

//MEMORY FUNCTIONS
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memalloc(size_t size);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_memdel(void **ptr);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

//STRING FUNCTIONS
char	**ft_split(char const *s, char c);
bool	ft_strbapi(char const *s, bool (*f)(int));
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_strdel(void **ptr);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnew(size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_strtoupper(char *string);
void	ft_strtolower(char *string);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// strclr
// striter
// striteri
// strequ
// strnequ
//MISCELLANEOUS FUNCTIONS
int		ft_atoi(const char *nptr);
long	ft_strtol(const char *nptr, char **endptr, int base);
char	*ft_itoa(int n);
size_t	ft_numlen(long long num);
size_t	ft_sgdnumlen(long long num);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_uitoa(unsigned int n);
char	*ft_uitoh(unsigned int n);
char	*ft_ultoh(unsigned long n);
int		*ft_arrint(int *array, int num, int len);
void	ft_swap(int *x, int *y);

//LIST FUNCTIONS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstadd_back(t_list **lst, t_list *lnew);
void	ft_lstadd_front(t_list **lst, t_list *lnew);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
//LIST IDEAS to implement
//ft_lsttravel
//ft_lstadd_after
//ft_lstsearch
//ft_lstprint

#endif
