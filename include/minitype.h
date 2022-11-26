#ifndef MINITYPE_H
# define MINITYPE_H

# include <stdbool.h>

bool	is_quotechar(const char c);
bool	ft_isdelimiter(const char sep);
bool	ft_isredir(const char redir);
bool	ft_ismetachar(const char meta_c);

#endif
